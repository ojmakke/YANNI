/*
 * logistic.hpp
 *
 *  Created on: Mar 17, 2016
 *      Author: Omar Makke
 */

#ifndef LOGISTIC_HPP_
#define LOGISTIC_HPP_

#include "activation.h"
#include <math.h>

template <typename T>
class  Logistic : public Activation<T>
{
public:
	/* <T> is casted to double and then back to <T> */
	T f(T fnet)
	{

		y = (T) 1.0/(1.0 + exp(-1.0 * ((double) -fnet)));
		fnet_old = fnet;
		return y;
	}
	/**
	 *  Derivative of tanh. T will be casted double and back from double
	 *   */
	T df(T fnet)
	{
		if(fnet != fnet_old)
		{
			y = (T) tanh((double) fnet);
			fnet_old = fnet;
		}
		return (T) y*(1.0-y);
	}
	~Logistic<T>(){}

private:
	T fnet_old;
	T y;
};



#endif /* LOGISTIC_HPP_ */
