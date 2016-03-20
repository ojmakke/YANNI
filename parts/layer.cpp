/*
 * layer.cpp
 *
 *  Created on: Mar 19, 2016
 *      Author: Omar Makke (O jMakke)
 */

#include <stdlib.h>
#include <stdio.h>
#include <vector>

#include "layer.h"
#include "node.h"
#include "../activation/activation.h"

template<typename T>
Layer<T>::Layer(size_t size, ActivationEnum switchin_function)
{
	if(size == 0)
	{
		fprintf(stderr, "Error in initializing Layer. Size is 0. Expect crash...\n");
		return;
	}
	for(size_t i = 0; i < size; i++)
	{
		Node<T> *node = new Node<T>(LOGISTIC);
		nodes.push_back(node);
	}
}

template<typename T>
Layer<T>::~Layer()
{
	fprintf(stdout, "Layer destructor called\n");
	if(nodes.size() == 0)
	{
		fprintf(stderr, "Attempting to destroy an incorrectly initialized layer.\nLuckily, you avoided crash!..\n");
		return;
	}
	fprintf(stdout, "Deleting layer nodes\n");
	// YAY, C++11
	for(auto *node : nodes)
	{
		delete node;
	}
}

template<typename T>
void Layer<T>::connect_to(Layer<T> &next_layer)
{
//	typedef typename std::vector<Node<T> *>::iterator v_iterator;

	if(nodes.size() == 0)
	{
		fprintf(stderr, "Layer has size of 0\n");
		return;
	}
	for(size_t i = 0; i < nodes.size(); i++)
	{
		if(next_layer.nodes.size() == 0)
		{
			fprintf(stderr, "Next layer has size of 0\n");
			return;
		}
		for(size_t j = 0; j < next_layer.nodes.size(); j++)
		{
			fprintf(stdout, "Connecting node %d to %d\n", (int) i, (int) i+1);
			Node<T> *i_node = nodes.at(i);
			Node<T> *j_node = next_layer.nodes.at(j);
			i_node->connect_to(j_node);
			fprintf(stdout, "Connection complete from node %d to %d\n", (int) i, (int) i+1);
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
		node_vector.push_back(i_node->get_output());
	}
	return node_vector;
}

template<typename T>
int Layer<T>::fix_layer_inputs(T *input_array, size_t input_size)
{
	if(nodes.size() != input_size || input_size == 0)
	{
		fprintf(stderr, "Incorrect input size\n");
		return 0;
	}

	Node<T> *i_node;
	for(size_t i = 0; i < input_size; i++)
	{
		//i_node = dynamic_cast<Node<T> *>(nodes.at(i));
		i_node = nodes.at(i);
		i_node->set_output(input_array[i]);
		i_node->is_input = true;
	}
	return 1;
}

template<typename T>
int Layer<T>::fix_some_layer_inputs(T* input_array_values, size_t *input_array_index, size_t input_size)
{
	if(input_size > nodes.size() || nodes.size() == 0)
	{
		fprintf(stderr, "Incorrect input size, too large\n");
		return 0;
	}

	Node<T> *i_node;
	for(size_t i = 0; i < input_size; i++)
	{
		if(input_array_index[i] >= nodes.size())
		{
			fprintf(stderr, "Incorrect value in input\n");
			return 0;
		}
		i_node =nodes.at(input_array_index[i]);
		i_node->set_output(input_array_values[i]);
	}
	return 1; // success
}

// Tell compiler which templates to compile
template class Layer<double>;
template class Layer<float>;
