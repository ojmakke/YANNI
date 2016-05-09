/*
 * fullhidden.cpp
 *
 *  Created on : Mar 19, 2016
 *      Author : Omar Makke (O jMakke)
 *      Email  : ojmakke@yahoo.com

This file is part of GNU Nets also known as GNUNets

GNU Nets is free software: you can redistribute it and/or modify
it under the terms of the Affero GNU General Public License as published by
the Free Software Foundation, version 3 of the License.

GNU Nets is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the Affero
GNU General Public License for more details.

You should have received a copy of the Affero GNU General Public License
along with GNU Nets.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <stdio.h>
#include <memory>
#include <math.h>

#include "common.h"
#include "parts/edge.h"
#include "parts/node.h"
#include "parts/layer.h"
#include "fileio/fileio.h"
#include "helper/console_printer.h"
#include "fullhidden.h"

void clear_2d(double** data, size_t dim);
void clear_2d(float** data, size_t dim);

template<typename T>
int FullHidden<T>::id = 0;

template<typename T>
FullHidden<T>::FullHidden():
  input_layer_size_(this->input_layer_size),
  output_layer_size_(this->output_layer_size),
  input_allocated(false),
  output_allocated(false),
  input_scale(1.0),
  output_scale(1.0)
{
  FullHidden::id++;
  self_id     = FullHidden::id;
  input_set = nullptr;
  output_set = nullptr;
  input_layer_size =  0;
  output_layer_size = 0;
  data_in_length = 0;
  data_out_length = 0;
  error_now = 100000.0;
  previous_error = 0.0;

}

/**
 * layers: array containing the size of each layer
 * layer_count: How many layers, i.e, layers size and switching functions size
 */
template<typename T>
FullHidden<T>::FullHidden(size_t *layers,
			  size_t layer_count,
			  ActivationEnum *switching_functions):
			  input_layer_size_(this->input_layer_size),
			  output_layer_size_(this->output_layer_size),
			  input_allocated(false),
			  output_allocated(false),
			  input_scale(1.0),
			  output_scale(1.0),
			  input_set(nullptr),
			  output_set(nullptr),
			  data_in_length(0),
			  data_out_length(0)
{

  // count before bias
  if(layer_count < 2)
    {
      return;
    }
  previous_error = 0.0;
  error_now = 100000.0;
  input_layer_size = layers[0];
  output_layer_size = layers[layer_count-1];
  FullHidden::id++;
  self_id = FullHidden::id;
  // Create layers and make last layer output,and first layer input
  for(size_t i = 0; i < layer_count; i++)
    {
      Layer<T> *i_layer = new Layer<T>(layers[i], switching_functions[i]);

      if(i == 0) // make input
        {
          for(size_t j = 0; j < layers[i]; j++)
            {
              Node<T> *j_node = (i_layer->nodes).at(j);
              j_node->is_input = true;
            }
        }
      else if(i == layer_count - 1)
        {
          for(size_t j = 0; j < layers[i]; j++)
            {
              Node<T> *j_node = (i_layer->nodes).at(j);
              j_node->is_output = true;
            }
        }
      all_layers.push_back(i_layer);
    }

  // Create bias nodes as input.
  for(size_t i = 0; i < layer_count-1; i++)
    {
      Layer<T> *i_layer = all_layers.at(i);
      i_layer->add_bias();
    }

  // connect the layers
  for(size_t i = 0; i < layer_count-1; i++)
    {
      Layer<T> *i_layer = all_layers.at(i);
      Layer<T> *i_next_layer = all_layers.at(i+1);
      i_layer->connect_to(*i_next_layer);
    }

}

template<typename T>
void FullHidden<T>::reset_weights()
{
  // loop through backward edges
  for(size_t ii = 1; ii < all_layers.size(); ii++)
    {
      Layer<T> *layer_ii = all_layers.at(ii);
      for(size_t jj = 0; jj < layer_ii->nodes.size(); jj++)
	{
	  Node<T> *node_jj = layer_ii->nodes.at(jj);
	  node_jj->reset_backward_weights();
	}
    }
}

template<typename T>
T FullHidden<T>::train()
{
  return (T) 0.01; 		// not implemented
}

template<typename T>
T FullHidden<T>::retrain()
{
  train(learning_target, epoch, learning_rate, dropoff);
}

template<typename T>
T FullHidden<T>::train(T target_error,
		       T epoch,
		       T learning_rate,
		       double dropoff)
{
  T error;
  this->learning_rate = learning_rate;
  this->epoch = epoch;
  this->learning_target = target_error;
  this->dropoff = dropoff;
  for(size_t study = 0; study < epoch; study++)
    {
      // We will calculate error as we go. Not the true error, but
      // more efficient. The proper way is to evaluate the error
      // for all the inputs after training. Imagine a huge training set!
      error = (T) 0.0;
      // dropoff enable
      Layer<T> *i_layer;
      Node<T> *j_node;
      Edge<T> *k_edge;

      for(size_t ii = 0; ii < all_layers.size()-1; ii++)
        {
          i_layer = all_layers.at(ii);
          for(size_t j = 0; j < i_layer->nodes.size(); j++)
            {
              j_node = i_layer->nodes.at(j);

              for(size_t k = 0; k < (j_node->forward).size(); k++)
                {
                  k_edge = (j_node->forward).at(k);
                  k_edge->req_rand_drop_off(dropoff); // for next loop
                }
            }
        }

      size_t set =
          (data_in_length <= data_out_length?data_in_length:data_out_length);
      //TODO
      // Create a stochastic approach to select inputs.
      T error_test = 0.0;

      for(size_t ii = 0; ii < set; ii++)
        {
	  train_pattern = train_pattern | 1;
          set_inputs((input_set)[ii]);
          forward_propagate();
          // Important. Run this first to get the first delta to propagate
          error += calc_error(output_set[ii]);
          back_propagate(this->learning_rate);
          update_weights(this->learning_rate);

        }
//      for(size_t i = 0; i < set; i++)
//        {
//          set_inputs((input_set)[i]);
//          forward_propagate_test();
//          error_test += calc_error(output_set[i]);
//
//        }
//      if(error == error_test)
//	{
//	 // this->learning_rate =this->learning_rate*1.1;
//	}
//      else if(error < error_test)
//	{
//	  this->learning_rate =this->learning_rate*0.9;
//	  for(size_t ii = 1; ii <= all_layers.size(); ii++)
//	    {
//	      // work backwards
//	      size_t index = all_layers.size() - ii;
//	      i_layer = all_layers.at(index);
//	      for(size_t jj = 0; jj < i_layer->nodes.size(); jj++)
//		{
//		  j_node = i_layer->nodes.at(jj);
//
//		  for(size_t kk = 0; kk < (j_node->forward).size(); kk++)
//		    {
//		      k_edge = (j_node->forward).at(kk);
////		      k_edge->undo_value();
//		    }
//		}
//	    }
////	  continue;
//	}
      // If 0, then batch
      if(!train_pattern)
	{
	  for(size_t ii = 1; ii <= all_layers.size(); ii++)
	    {
	      // work backwards
	      size_t index = all_layers.size() - ii;
	      i_layer = all_layers.at(index);
	      for(size_t jj = 0; jj < i_layer->nodes.size(); jj++)
		{
		  j_node = i_layer->nodes.at(jj);

		  for(size_t kk = 0; kk < (j_node->forward).size(); kk++)
		    {
		      k_edge = (j_node->forward).at(kk);
		      k_edge->confirm_value();
		    }
		}
	    }
	}


      std::string result = "Error in ";
      result.append(std::to_string(study)
                    .append(" is ")
                    .append(std::to_string(error)));
      ConsolePrinter::instance().feedback_overwrite(result);
      if(error <= target_error)
        {
          return error;
        }
    }

  Layer<T> *i_layer;
  Node<T> *j_node;
  Edge<T> *k_edge;

  for(size_t ii = 0; ii < all_layers.size()-1; ii++)
    {
      i_layer = all_layers.at(ii);
      for(size_t j = 0; j < i_layer->nodes.size(); j++)
        {
          j_node = i_layer->nodes.at(j);

          for(size_t k = 0; k < (j_node->forward).size(); k++)
            {
              k_edge = (j_node->forward).at(k);
              k_edge->req_drop_off(false); // for next loop
            }
        }
    }
    // reset drop_off


//  fprintf(stdout, "\n");
  return error;
}

template<typename T>
void FullHidden<T>::dump_everything()
{
  // For each layer
  for(size_t i = 0; i < all_layers.size(); i++)
    {
//      fprintf(stdout, "\n\nLayer %d:\n", (int) i);
      Layer<T> *i_layer = all_layers.at(i);

      // Get the nodes
      std::vector<Node<T> *> i_all_nodes = i_layer->nodes;

      // For each node in layer
      for(size_t j = 0; j < i_all_nodes.size(); j++)
        {
          Node<T> *j_node = i_all_nodes.at(j);
//         fprintf(stdout, "Node %d: \t\tValue: %f\tNet: %f\n",
//                  (int) j,
//                  (float) j_node->get_output(),
//                  (float) j_node->get_net());
          // Get the edges of the node input. Input layer doesn't have them
          if(j_node->is_input)
            {
              continue;
            }
          std::vector<Edge<T> *> j_all_edges = j_node->backward;

//          for(size_t k = 0; k <j_all_edges.size(); k++)
//            {
//              Edge<T> *k_edge = j_all_edges.at(k);
//              fprintf(stdout, "Edge %d: \t\tValue: %f\n",
//                      (int) k,
//                      (float) k_edge->get_value() );
//            }
        }
    }
}

template<typename T>
void FullHidden<T>::forward_propagate()
{
    // reset drop_off

  for(size_t ii = 0; ii < all_layers.size(); ii++)
    {
      Layer<T> *i_layer = all_layers.at(ii);
      std::vector<Node<T> *> i_nodes = i_layer->nodes;

      for(size_t jj = 0; jj < i_nodes.size(); jj++)
        {
          Node<T> *j_node = i_nodes.at(jj);
          j_node->calc_new_output();
          //			fprintf(stdout, " %f ", j_node->get_output());
        }
    }
}

template<typename T>
void FullHidden<T>::forward_propagate_test()
{
    // reset drop_off

  for(size_t ii = 0; ii < all_layers.size(); ii++)
    {
      Layer<T> *i_layer = all_layers.at(ii);
      std::vector<Node<T> *> i_nodes = i_layer->nodes;

      for(size_t jj = 0; jj < i_nodes.size(); jj++)
        {
          Node<T> *j_node = i_nodes.at(jj);
          j_node->calc_new_output_test();
          //			fprintf(stdout, " %f ", j_node->get_output());
        }
    }
}

template<typename T>
void FullHidden<T>::set_inputs(T *inputs)
{
  if(all_layers.size() <= 1)
    {
      return;
    }

  Layer<T> *layer = all_layers.at(0);

  layer->fix_layer_inputs(inputs);
  return;
}

template<typename T>
void FullHidden<T>::dump_outputs()
{
  Layer<T> *output_layer = all_layers.at(all_layers.size()-1);

  for(size_t ii = 0; ii < (output_layer->nodes).size(); ii++)
    {
      std::string outstr = "Output ";
      Node<T> *i_node = (output_layer->nodes).at(ii);
      outstr.append(std::to_string(ii))
          .append(": Value: ")
          .append(std::to_string(i_node->y_));

      ConsolePrinter::instance().feedback_write(outstr);
    }
}

template<typename T>
std::unique_ptr<T[]> FullHidden<T>::get_output()
{

  Layer<T> *output_layer = all_layers.at(all_layers.size()-1);
  std::unique_ptr<T[]> out (new T[(output_layer->nodes).size()]);

  for(size_t ii = 0; ii < (output_layer->nodes).size(); ii++)
    {
      Node<T> *i_node = (output_layer->nodes).at(ii);
      out[ii] = i_node->y_;
    }
  return out;
}

template<typename T>
void FullHidden<T>::back_propagate(T rate)
{
  // Loop through each node in every layer except input and output
  // The output layer nodes must already have its delta calculated
  // Update delta.
  // Calc delta weight and update weights.
  for(size_t ii = 1; ii < all_layers.size(); ii++)
    {
      // backwards. size_t cannot go below 0, cannot do < size_t
      size_t jj = all_layers.size() - ii -1;	//skip output.
      Layer<T> *layer = all_layers.at(jj);
      layer->calc_node_delta();
    }
}

/*
 * Calculates error, and also delta for output layer
 */
template<typename T>
T FullHidden<T>::calc_error(T *target)
{
  T sum = (T) 0.0;
  T diff;
  Layer<T> *output = all_layers.at(all_layers.size()-1);

  for(size_t ii = 0; ii < output->nodes.size(); ii++)
    {
      Node<T> *i_node = output->nodes.at(ii);
      diff = target[ii] - i_node->y_;
      sum += diff*diff;
      // delta local to the node. This will be summed up later.
      T delta = (T) -1.0f*diff*i_node->F->df(i_node->fnet_);
      i_node->req_delta(delta);
    }
  return sum;
}

template<typename T>
void FullHidden<T>::update_weights(T rate)
{
  Layer<T> *i_layer;
  Node<T> *j_node;
  Edge<T> *k_edge;

  for(size_t ii = 1; ii <= all_layers.size(); ii++)
    {
      // work backwards
      size_t index = all_layers.size() - ii;
      i_layer = all_layers.at(index);
      for(size_t jj = 0; jj < i_layer->nodes.size(); jj++)
        {
          j_node = i_layer->nodes.at(jj);

          for(size_t kk = 0; kk < (j_node->forward).size(); kk++)
            {
              k_edge = (j_node->forward).at(kk);
              const Node<T> *k_node = k_edge->n_;
              T dw = (rate*k_node->delta_*j_node->y_);
              if(dw == 0)
        	{
        	  return;
        	}
              k_edge->accumulate(dw);
              if(train_pattern) k_edge->confirm_value();	// one = online
            }
        }
    }
}

template<typename T>
NNInfo_uptr FullHidden<T>::input_file_alloc(std::string filename)
{
  NNInfo_uptr ret = default_info();
  Layer<T> *layer = all_layers.at(0);

  if(input_allocated)
    {
      // don't forget that input layer has bias!
      clear_2d(input_set, data_in_length);
    }
  // ASSUMPTION
  // This function is read before output.
  ret->stack = FileIO::get_text_1D(filename,
				   layer->nodes.size()-1,
				   (double*** )&input_set,
				   &data_in_length);

  append_info(ret);
  if(data_in_length > 0)
    {
      input_allocated = true;
    }
  else
    {
      input_allocated = false; // in case bad file was loaded after
    }
  return ret;
}

template<typename T>
NNInfo_uptr FullHidden<T>::output_file_alloc(std::string filename)
{
  NNInfo_uptr ret = default_info();
  Layer<T> *layer = all_layers.at(all_layers.size()-1);

  if(output_allocated)
    {
      clear_2d(output_set, data_out_length);
    }

  // ASSUMPTION
  // input_file_alloc called first
  // Execute the function and get the result
  ret->stack = FileIO::get_text_1D(filename,
				   layer->nodes.size(),
				   (double*** )&output_set,
				   &data_out_length);
  // stack the error if stack has error
  append_info(ret);
  LEAVE_ON_ERROR(ret);

  if(data_out_length != data_in_length)
    {
      ret->result = NNERROR;
      ret->message = MSG::FILE_MISMATCH;
    }

  // TODO
  // Verify memory allocation and release is correct. Flags are ugly.
  if(data_out_length > 0)
    {
      output_allocated = true;
    }
  else
    {
      output_allocated = false;
    }
  return ret;
}

void clear_2d(double** data, size_t dim)
{
  for(size_t ii = 0; ii < dim; ii++)
    {
      delete[] data[ii];
    }
  if(dim > 0)
    {
      delete [] data;
    }
}
void clear_2d(float** data, size_t dim)
{
  for(size_t ii = 0; ii < dim; ii++)
    {
      delete[] data[ii];
    }
  if(dim > 0)
    {
      delete [] data;
    }
}
template<typename T>
FullHidden<T>::~FullHidden()
{
  // Important to make sure not to allocate these until it is checked
  // that input matches input and output dimensions matches output
  if(input_allocated)
    {
      Layer<T> *layer = all_layers.at(0);
      clear_2d(input_set, layer->nodes.size());
      input_allocated = false;
    }
  if(output_allocated)
    {
      Layer<T> *layer = all_layers.at(all_layers.size()-1);
      clear_2d(output_set, layer->nodes.size());
      output_allocated = false;
    }

  for(size_t i = 0; i <  all_layers.size(); i++)
    {
      Layer<T> *last_layer = all_layers.at(i);
      delete last_layer;
    }
  all_layers.clear();
}

// Tell compiler which classes will be used
template class FullHidden<double>;
template class FullHidden<float>;
