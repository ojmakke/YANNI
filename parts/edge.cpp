/*
 * edge.cpp
 *
 *  Created on: Mar 17, 2016
 *      Author: Omar Makke
 */

#include <random>
#include <cstdlib>
#include <ctime>

#include "edge.h"
#include "../helper/nnhelper.hpp"


extern NNHelper<double> nnhelper;

template<typename T>
T Edge<T>::getValue()
{
	if(this->isConnected)
	{
		return this->value;
	}
	return (T) 0.0;
}

template<typename T>
void Edge<T>::setValue(T edge_value)
{
	if(this->isConnected)
	{
		this->value = edge_value;
	}
	// else do nothing

}

template<typename T>
Edge<T>::Edge()
{
	if(this->isConnected)
		this->value = nnhelper.randomizer.getRand();
}

template<typename T>
Edge<T>::Edge(T v)
{
	this->value = v;
	this->isConnected = true;
}
