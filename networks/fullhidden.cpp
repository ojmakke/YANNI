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

template<typename T>
FullHidden<T>::FullHidden(size_t *layers, size_t layer_count, ActivationEnum *switching_functions)
{
	fprintf(stdout, "Creating the hidden network\n");
	if(layer_count < 2)
	{
		fprintf(stderr, "Need at least 2 layers (input, output) for Full Hidden network\n");
		return;
	}

	for(size_t i = 0; i < layer_count; i++)
	{
		fprintf(stdout, "Creating layer %d\n", (int) i);
		Layer<T> *i_layer = new Layer<T>(layers[i], switching_functions[i]);
		all_layers.push_back(i_layer);
	}

	for(size_t i = 0; i < layer_count-1; i++)
	{
		fprintf(stdout, "Connecting layer %d to %d\n", (int) i, (int) i+1);
		Layer<T> *i_layer = all_layers.at(i);
		Layer<T> *i_next_layer = all_layers.at(i+1);
		i_layer->connect_to(*i_next_layer);
		fprintf(stdout, "Layer connection from %d to %d is complete\n", (int) i, (int) i+1);
	}
	// Now create the connections
}

template<typename T>
FullHidden<T>::~FullHidden()
{
	fprintf(stdout, "Full Hidden Network destructor called\n");
	for(size_t i = 0; i <  all_layers.size(); i++)
	{
		fprintf(stdout, "Deleting layer %d\n", (int) i);
		Layer<T> *last_layer = all_layers.at(i);
		delete last_layer;
	}
	all_layers.clear();
}

template<typename T>
T FullHidden<T>::train()
{
	return (T) 0.01;
}

template<typename T>
T FullHidden<T>::train(T target_error, T epoch, T learning_rate)
{
	return (T) 0.01;
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

// Tell compiler which classes will be used
template class FullHidden<double>;
template class FullHidden<float>;
