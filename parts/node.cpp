/*
 * node.cpp
 *
 *  Created on: Mar 17, 2016
 *      Author: Omar Makke (O jMakke)
 */

#include <vector>

#include "node.h"
#include "edge.h"
#include "../activation/activation.h"
#include "../activation/logistic.hpp"
#include "../activation/step.hpp"
#include "../activation/rectify.hpp"
#include "../activation/tanh.hpp"
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
	}
}

template<typename T>
Node<T>::~Node()
{
	// Remember, as you see in connectTo(), edges are created in node. Therefore, node clears them.
	// The "Next edge

	fprintf(stdout, "Node destructor called\n");
	if(forward.size() == 0)
	{
		fprintf(stdout, "No forward edges to delete\n");
	}
	else
	{
		for(size_t i = 0; i < forward.size(); i++)
		{
			fprintf(stdout, "Deleting forwad edge %d\n", (int) i);
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
	fprintf(stdout, "Creating edge\n");
	// Create an edge
	Edge<T> *edge = new Edge<T>();

	edge->set_value((T) nnhelper.randomizer.get_rand());
	fprintf(stdout, "Some random number: %f\n", (float) edge->get_value());
	edge->n = node;
	edge->p = this;

	// Store the edge in both nodes
	forward.push_back(edge);
	fprintf(stdout, "Setting edge in next node\n");
	std::vector<Edge<T> *> *backward = &(node->backward); 		// This node is behind the next node
	fprintf(stdout, "Edge obtained\n");
	backward->push_back(edge);
	fprintf(stdout, "Edge connected\n");
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


// Tell compiler which classes to compile
template class Node<double>;
template class Node<float>;
