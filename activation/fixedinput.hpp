/*
 * fixedinput.cpp
 *
 *  Created on: Mar 17, 2016
 *      Author: Omar Makke (O jMakke)
 *      ojQuote: "Programming is a science and coding is an art"
 */

#ifndef FIXEDINPUT_HPP_
#define FIXEDINPUT_HPP_

#include "activation.h"
#include <math.h>

template <typename T>
class  FixedInput : public Activation<T>
{
public:
	/* <T> is casted to double and then back to <T> */
	T f(T fnet)
	{
		return (T) 1.0;
	}
	T df(T fnet)
	{
		return (T) 0.0;
	}
	~FixedInput<T>(){}
};
template class FixedInput<double>;
template class FixedInput<float>;
#endif /* FIXEDINPUT_HPP_ */


