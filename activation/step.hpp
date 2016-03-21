/*
 * step.hpp
 *
 *  Created on: Mar 17, 2016
 *      Author: Omar Makke (Omar jMakke)
 *      ojQuote: "Freedom of speech? More like freedom to impeach!"
 */

#ifndef STEP_HPP_
#define STEP_HPP_

#include "activation.h"
#include <stdio.h>
#include <math.h>

template <typename T>
class  Step : public Activation<T>
{
public:
	/* <T> is casted to double and then back to <T> */
	T f(T fnet)
	{
		if((double) fnet < 0.0)
		{
			return (T) 0.0;
		}
		return (T) 1.0;
	}
	/**
	 *  Derivative. T will be casted double and back from double
	 *   */
	T df(T fnet)
	{
		if((double) fnet == 0.0)
		{
			fprintf(stderr, "Invalid derivative for Step\n");
			return (T) 0.0;
		}
		return (T) 0.0;
	}
	~Step<T>(){}
};
template class Step<double>;
template class Step<float>;

#endif /* STEP_HPP_ */
