/*
 * node.cpp
 *
 *  Created on: Mar 17, 2016
 *      Author: Omar Makke
 */

#include <vector>

#include "node.h"
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
	switch(type)
	{
		case LOGISTIC:
		{
			this->F =  Logistic<T>();
			break;
		}
		case TANH:
		{
			this->F = Tanh<T>();
			break;
		}
		case RECTIFY:
		{
			this->F = Rectify<T>();
			break;
		}
		case STEP:
		{
			this->F = Step<T>();
			break;
		}
	}
}

template<typename T>
Node<T>::~Node()
{
	// Remember, as you see in connectTo(), edges are created in node. Therefore, node clears them.
	// The "Next edge
	for(auto *e : forward)
	{
		delete e;
		e = nullptr;
	}

//	// Now clean the vectors
//	typename std::vector<Edge<T>*>::iterator it;
//	for(it = forward.begin(); it != forward.end(); it++)

}

template<typename T>
void Node<T>::connectTo(Node<T> *node)
{
	// Create an edge
	Edge<T> *edge = new Edge<T>();
	*edge->value = (T) nnhelper.randomizer.getRand();
	edge->n = node;
	edge->p = this;

	// Store the edge in both nodes
	forward.push_back(*edge);
	std::vector<Edge<T> *> *backward = &(node->backward); 		// This node is behind the next node
	*backward->push_back(edge);
	return;
}
