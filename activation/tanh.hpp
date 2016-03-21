/*
 * tanh.cpp
 *
 *  Created on: Mar 17, 2016
 *      Author: Omar Makke (O jMakke)
 *      ojQuote: "A: How many meanings does "free" have? B: Which year?"
 */

#ifndef TANH_HPP_
#define TANH_HPP_

#include "activation.h"
#include <math.h>

template <typename T>
class  Tanh : public Activation<T>
{
	private:
	T fnet_old ;
	T y;

public:
	/* <T> is casted to double and then back to <T> */
	T f(T fnet)
	{
		y = (T) tanh((double) fnet);
		fnet_old  = fnet;
		return y;
	}
	/**
	 *  Derivative of tanh. T will be casted double and back from double
	 *   */
	T df(T fnet)
	{
		if(fnet != fnet_old )
		{
			y = (T) tanh((double) fnet);
			fnet_old = fnet;
		}
		return (T) (1 - y*y);
	}
	~Tanh<T>(){}
};
template class Tanh<double>;
template class Tanh<float>;
#endif /* TANH_HPP_ */


