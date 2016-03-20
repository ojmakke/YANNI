/*
 * edge.cpp
 *
 *  Created on: Mar 17, 2016
 *      Author: Omar Makke (O jMakke)
 *
 */

#include <random>
#include <cstdlib>
#include <ctime>

#include "edge.h"
#include "../helper/nnhelper.hpp"


extern NNHelper<double> nnhelper;

template<typename T>
T Edge<T>::get_value()
{
	if(this->is_connected)
	{
		return this->value;
	}
	return (T) 0.0;
}

template<typename T>
void Edge<T>::set_value(T edge_value)
{
	if(this->is_connected)
	{
		this->value = edge_value;
	}
	// else do nothing

}

template<typename T>
Edge<T>::Edge()
{
	this->value = nnhelper.randomizer.get_rand();
	this->is_connected = true;
}

template<typename T>
Edge<T>::Edge(T v)
{
	this->value = v;
	this->is_connected = true;
}

// Tell compiler what to build
template class Edge<double>;
template class Edge<float>;
