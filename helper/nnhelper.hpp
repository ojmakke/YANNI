/*
 * helper.cpp
 *
 *  Created on: Mar 17, 2016
 *      Author: Omar Makke
 */

#ifndef NNHELPER_HPP_
#define NNHELPER_HPP_

#include "randomizer.h"

template <typename T>
class NNHelper
{
public:
	Randomizer<T> randomizer;

	NNHelper();
	~NNHelper();
};

template<typename T>
NNHelper<T>::NNHelper()
{
	Randomizer<T> x;
	randomizer = x;
}

template<typename T>
NNHelper<T>::~NNHelper()
{

}

#endif /* NNHELPER_HPP_ */

