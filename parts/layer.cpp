/*
 * layer.cpp
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
#include <vector>

#include "layer.h"
#include "node.h"
#include "../activation/activation.h"
#include "../helper/console_printer.h"

template<typename T>
Layer<T>::Layer(size_t size, ActivationEnum switching_function)
{
  if(size == 0)
    {
      return;
    }
  for(size_t i = 0; i < size; i++)
    {
      Node<T> *node = new Node<T>(switching_function);
      nodes.push_back(node);
    }
}

template<typename T>
Layer<T>::~Layer()
{
  if(nodes.size() == 0)
    {
      return;
    }
  // YAY, C++11
  for(auto *node : nodes)
    {
      delete node;
    }
}

// Note: If the next node has an input node, like a bias,
// nodes from previous layers will not be connected to it.
template<typename T>
void Layer<T>::connect_to(Layer<T> &next_layer)
{
  //	typedef typename std::vector<Node<T> *>::iterator v_iterator;

  if(nodes.size() == 0)
    {
  //    fprintf(stderr, "Layer has size of 0\n");
      return;
    }
  for(size_t i = 0; i < nodes.size(); i++)
    {
      if(next_layer.nodes.size() == 0)
        {
 //         fprintf(stderr, "Next layer has size of 0\n");
          return;

        }
      Node<T> *i_node = nodes.at(i);
      for(size_t j = 0; j < next_layer.nodes.size(); j++)
        {
          Node<T> *j_node = next_layer.nodes.at(j);
          if(j_node->is_input)
            {
              continue;	// Ignore any input such as bias.
            }
          i_node->connect_to(j_node);
        }
    }
}

// Returns a vector of <T> Values.
template<typename T>
std::vector<T> Layer<T>::get_layer_outputs()
{
  std::vector<T> node_vector;
  //	typedef typename std::vector<Node<T> *>::iterator v_iterator;
  for(unsigned int i = 0; i < nodes.size(); i++)
    {
      Node<T> *i_node = nodes.at(i);
      node_vector.push_back(i_node->y_);
    }
  return node_vector;
}

// Note: Size is assumed to be = to nodes.size() - 1, and bias already exits.
template<typename T>
int Layer<T>::fix_layer_inputs(T *input_array)
{
  if(nodes.size() == 0)
    {
  //    fprintf(stderr, "Incorrect input layer size\n");
      return 0;
    }

  Node<T> *i_node;
  for(size_t i = 0; i < nodes.size()-1; i++)
    {
      //i_node = dynamic_cast<Node<T> *>(nodes.at(i));
      i_node = nodes.at(i);
      i_node->req_output(input_array[i]);
      i_node->is_input = true;
    }
  return 1;
}

template<typename T>
int Layer<T>::fix_some_layer_inputs(T* input_array_values,
				    size_t *input_array_index,
				    size_t input_size)
{
  if(input_size > nodes.size() || nodes.size() == 0)
    {
  //    fprintf(stderr, "Incorrect input size, too large\n");
      return 0;
    }

  Node<T> *i_node;
  for(size_t i = 0; i < input_size; i++)
    {
      if(input_array_index[i] >= nodes.size())
        {
      //    fprintf(stderr, "Incorrect value in input\n");
          return 0;
        }
      i_node =nodes.at(input_array_index[i]);
      i_node->req_output(input_array_values[i]);
    }
  return 1; // success
}

template<typename T>
void Layer<T>::add_bias()
{
  // Now create bias
  Node<T> *node = new Node<T>(FIXEDINPUT);
  // yay, nice use of is input! Didn't think about it then.
  node->is_input = true;
  node->req_output((T) 1.0);
  nodes.push_back(node);		// This will also add bias to the output
}



/*
 * Calculates the delta of each node individually.
 */
template<typename T>
void Layer<T>::calc_node_delta()
{
  Node<T> *i_node;
  Edge<T> *j_edge;
  T delta = (T) 0.0;
  for(size_t i = 0; i < nodes.size(); i++)
    {
      i_node = nodes.at(i);
      // Do nothing for input and output layers.
      if(i_node->is_input || i_node ->is_output)
        {
          return;
        }
      // Sum over edges.
      for(size_t j = 0; j < (i_node->forward).size(); j++)
        {
          j_edge = (i_node->forward).at(j);

          // summation( w_exiting_edges*delta_of_next_neuron*this_neuron_derivative
          const Node<T> *j_node = j_edge->n_;
          if(fabs(j_node->delta_) > 1000)
            {
 //             ConsolePrinter::instance().feedback_write("High Next Node");
 //             abort();
            }
          if(fabs(j_edge->value_) > 100)
            {
  //            ConsolePrinter::instance().feedback_write("High Next Edge");
  //            abort();
            }
          delta += j_edge->value_ * (j_node->delta_);
        }
      Activation<T> *f = i_node->F;
      delta *= f->df(i_node->fnet_);;
      if(isnan(delta))
	{
//	   ConsolePrinter::instance().feedback_write("High Delta");
//	   abort();
	}

      if(fabs(delta) > 10)
	{
//	   ConsolePrinter::instance().feedback_write("High Delta10");
//	   abort();
	}
      i_node->req_delta(delta);
    }

  return;
}

// Tell compiler which templates to compile
template class Layer<double>;
template class Layer<float>;
