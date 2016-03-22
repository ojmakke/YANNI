/*
 * node.cpp
 *
 *  Created on : Mar 17, 2016
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

#include <vector>

#include "node.h"
#include "edge.h"
#include "../activation/activation.h"
#include "../activation/logistic.hpp"
#include "../activation/step.hpp"
#include "../activation/rectify.hpp"
#include "../activation/tanh.hpp"
#include "../activation/fixedinput.hpp"
#include "../helper/nnhelper.hpp"


extern NNHelper<double> nnhelper;
//template<typename T>
//Node<T>::Node(size_t outputs, size_t inputs, ActivationEnum type)
//{
//
//}
template<typename T>
Node<T>::Node(ActivationEnum type)
{
	is_input=false;
	is_output=false;
	delta = (T) 0.0;
	switch(type)
	{
		case LOGISTIC:
		{
			F =  new Logistic<T>();
			break;
		}
		case TANH:
		{
			F = new Tanh<T>();
			break;
		}
		case RECTIFY:
		{
			F = new Rectify<T>();
			break;
		}
		case STEP:
		{
			F = new Step<T>();
			break;
		}
		case FIXEDINPUT:
		{
			F = new FixedInput<T>();
			break;
		}
	}
}

template<typename T>
Node<T>::~Node()
{
	// Remember, as you see in connectTo(), edges are created in node.
	// Therefore, node clears them.
	// The "Next edge

//	fprintf(stdout, "Node destructor called\n");
	if(forward.size() == 0)
	{
//		fprintf(stdout, "No forward edges to delete\n");
	}
	else
	{
		for(size_t i = 0; i < forward.size(); i++)
		{
//			fprintf(stdout, "Deleting forwad edge %d\n", (int) i);
			Edge<T> *edge = forward.at(i);
			delete(edge);
		}
	}
	delete F;

//	// Now clean the vectors
//	typename std::vector<Edge<T>*>::iterator it;
//	for(it = forward.begin(); it != forward.end(); it++)

}

template<typename T>
void Node<T>::connect_to(Node<T> *node)
{
//	fprintf(stdout, "Creating edge\n");
	// Create an edge
	Edge<T> *edge = new Edge<T>();

	edge->set_value((T) nnhelper.randomizer.get_rand());
//	fprintf(stdout, "Some random number: %f\n", (float) edge->get_value());
	edge->n = node;
	edge->p = this;

	// Store the edge in both nodes
	forward.push_back(edge);
//	fprintf(stdout, "Setting edge in next node\n");

	// This node is behind the next node
	std::vector<Edge<T> *> *backward = &(node->backward);
//	fprintf(stdout, "Edge obtained\n");
	backward->push_back(edge);
//	fprintf(stdout, "Edge connected\n");
	return;
}

template<typename T>
T Node<T>::get_output()
{
	return y;
}

template<typename T>
T Node<T>::get_net()
{
	return fnet;
}

template<typename T>
void Node<T>::set_output(T output)
{
	y = output;
}

//TODO
// Abstract calculation method to allow parallel computing
// Add dirty flag to avoid re-calculation if nothing has changed.
// Dirty flag will go into the node and is set when edge states are updated
template<typename T>
T Node<T>::calc_new_output()
{
	// Input doesn't have input edges.
	if(is_input)
	{
//		fprintf(stdout, "Returning y = %f\n", y);
		return y;
	}

	fnet = (T) 0.0;
	// Loop through all edges
	for(size_t i = 0; i < backward.size(); i++)
	{
		Edge<T> *i_edge = backward.at(i);
		// previous node connecting to current node through the edge
		Node<T>  *i_node = i_edge->p;
		fnet += i_edge->get_value() * i_node->get_output();
	}
	y = F->f(fnet);
	return (T) y;	// Optional. Doesn't have to be used.
}

template<typename T>
T Node<T>::get_delta()
{
	return delta;
}

template<typename T>
void Node<T>::set_delta(T _delta)
{
//	if(!is_output)
//	{
//		fprintf(stderr, "Attempting to control delta of hidden neuron\n");
//		return;
//	}

	this->delta = _delta;
}

// Tell compiler which classes to compile
template class Node<double>;
template class Node<float>;
