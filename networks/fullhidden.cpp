/*
 * fullhidden.cpp
 *
 *  Created on: Mar 19, 2016
 *      Author: Omar Makke (O jMakke)
 */

#include <stdlib.h>
#include <stdio.h>

#include "../parts/edge.h"
#include "../parts/node.h"
#include "../parts/layer.h"
#include "fullhidden.h"

template<typename T>
FullHidden<T>::FullHidden()
{
}

/**
 * layers: array containing the size of each layer
 * layer_count: How many layers, i.e, layers size and switching functions size
 */
template<typename T>
FullHidden<T>::FullHidden(size_t *layers, size_t layer_count, ActivationEnum *switching_functions)
{
	fprintf(stdout, "Creating the hidden network\n");
	if(layer_count < 2)
	{
		fprintf(stderr, "Need at least 2 layers (input, output) for Full Hidden network\n");
		return;
	}

	// Create layers and make last layer ouput,and first layer input
	for(size_t i = 0; i < layer_count; i++)
	{
		fprintf(stdout, "Creating layer %d of size %d\n", (int) i, (int) layers[i]);
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

	for(size_t i = 0; i < layer_count-1; i++)
	{
//		fprintf(stdout, "Connecting layer %d to %d\n", (int) i, (int) i+1);
		Layer<T> *i_layer = all_layers.at(i);
		Layer<T> *i_next_layer = all_layers.at(i+1);
		i_layer->connect_to(*i_next_layer);
//		fprintf(stdout, "Layer connection from %d to %d is complete\n", (int) i, (int) i+1);
	}

	// Add bias to all except output and input
	for(size_t i = 0; i < layer_count-2; i++)
	{
		fprintf(stdout, "Creating bias in layer %d\n", (int) i);
		Layer<T> *i_layer = all_layers.at(i+1);
		i_layer->add_bias(switching_functions[i]);
		fprintf(stdout, "Layer connection from %d to %d is complete\n", (int) i, (int) i+1);
	}
	// This will also add bias to the output
}

template<typename T>
FullHidden<T>::~FullHidden()
{
//	fprintf(stdout, "Full Hidden Network destructor called\n");
	for(size_t i = 0; i <  all_layers.size(); i++)
	{
		fprintf(stdout, "Deleting layer %d\n", (int) i);
		Layer<T> *last_layer = all_layers.at(i);
		delete last_layer;
	}
	fprintf(stdout, "Deleting layers is complete\n");
	all_layers.clear();
}

template<typename T>
T FullHidden<T>::train(__training_struct<T>  *training_data)
{
	return (T) 0.01; 		// not implemented
}

template<typename T>
T FullHidden<T>::train(__training_struct<T>  *training_data, T target_error, T epoch, T learning_rate)
{
	T error;
	for(size_t study = 0; study < epoch; study++)
	{
		error = (T) 0.0;	// We will calculate error as we go. Not the true error, but
							// much more efficient. The proper way is to evaluate the error
							// for all the inputs after training. Imagine a huge training set!

		//TODO
		// Create a stochastic approach to select inputs.
		for(size_t i = 0; i < training_data->x; i++)
		{
			set_inputs((training_data->input_set)[i]);
			forward_propagate();
			// Important. Run this first to get the first delta to propagate
			error += calc_error((training_data->target_set)[i]);
			back_propagate(learning_rate);
			update_weights(learning_rate);	// Does this have to be part of back_propagate?
		}
		fprintf(stdout, "Error in %d is %f\n", study, error);
		if(error <= target_error)
		{
			return error;
		}
	}
	return error;
}

template<typename T>
void FullHidden<T>::dump_everything()
{
	// For each layer
	for(size_t i = 0; i < all_layers.size(); i++)
	{
		fprintf(stdout, "\n\nLayer %d:\n", (int) i);
		Layer<T> *i_layer = all_layers.at(i);

		// Get the nodes
		std::vector<Node<T> *> i_all_nodes = i_layer->nodes;

		// For each node in layer
		for(size_t j = 0; j < i_all_nodes.size(); j++)
		{
			Node<T> *j_node = i_all_nodes.at(j);
			fprintf(stdout, "Node %d: \t\tValue: %f\tNet: %f\n", (int) j, (float) j_node->get_output(), (float) j_node->get_net());
			// Get the edges of the node input. Input layer doesn't have them
			if(j_node->is_input)
			{
				continue;
			}
			std::vector<Edge<T> *> j_all_edges = j_node->backward;

			for(size_t k = 0; k <j_all_edges.size(); k++)
			{
				Edge<T> *k_edge = j_all_edges.at(k);
				fprintf(stdout, "Edge %d: \t\tValue: %f\n", (int) k, (float) k_edge->get_value() );
			}
		}
	}
}

template<typename T>
void FullHidden<T>::forward_propagate()
{
	for(size_t i = 0; i < all_layers.size(); i++)
	{
		Layer<T> *i_layer = all_layers.at(i);
		std::vector<Node<T> *> i_nodes = i_layer->nodes;

		for(size_t j = 0; j < i_nodes.size(); j++)
		{
			Node<T> *j_node = i_nodes.at(j);
			j_node->calc_new_output();
//			fprintf(stdout, " %f ", j_node->get_output());
		}
	}
}

template<typename T>
void FullHidden<T>::set_inputs(T *inputs)
{
	if(all_layers.size() <= 1)
	{
		fprintf(stderr, "Network does not have input and output layers\n");
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
	fprintf(stdout, "Last layer has size:%d\n", output_layer->nodes.size());
	for(size_t i = 0; i < (output_layer->nodes).size(); i++)
	{
		Node<T> *i_node = (output_layer->nodes).at(i);
		fprintf(stdout, "Output %d  :\tValue  :%f\n",(int) i, (float) i_node->get_output());
	}
}

template<typename T>
void FullHidden<T>::back_propagate(T rate)
{
	// Loop through each node in every layer except input and output
	// The output layer nodes must already have its delta calculated
	// Update delta.
	// Calc delta weight and update weights.
	for(size_t i = 0; i < all_layers.size()-2; i++)
	{
		// backwards. size_t cannot go below 0, hence will not reverse the loop
		size_t j = all_layers.size()-2 - i;	//skip output.
		Layer<T> *layer = all_layers.at(j);
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

	for(size_t i = 0; i < output->nodes.size(); i++)
	{
		Node<T> *i_node = output->nodes.at(i);
		diff = target[i] - i_node->get_output();
		sum += diff*diff;
		// delta local to the node. This will be summed up later.
		i_node->set_delta((T) -1.0f*diff*i_node->F->df(i_node->get_net()));
	}
	return sum;
}

template<typename T>
void FullHidden<T>::update_weights(T rate)
{
	Layer<T> *i_layer;
	Node<T> *j_node;
	Edge<T> *k_edge;
	Node<T> *k_node;
	for(size_t i = 0; i < all_layers.size() - 1; i++)
	{
		// work backwards
		size_t index = all_layers.size() - 1 - i;
		i_layer = all_layers.at(index);
		for(size_t j = 0; j < i_layer->nodes.size(); j++)
		{
			j_node = i_layer->nodes.at(j);

			for(size_t k = 0; k < (j_node->forward).size(); k++)
			{
				k_edge = (j_node->forward).at(k);
				k_node = k_edge->n;
				T w = k_edge->get_value() - (rate*k_node->get_delta()*j_node->get_output());
				k_edge->set_value(w);
			}
		}
	}
}

// Tell compiler which classes will be used
template class FullHidden<double>;
template class FullHidden<float>;
