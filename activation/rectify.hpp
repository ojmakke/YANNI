/*
 * rectify.hpp
 *
 *  Created on: Mar 17, 2016
 *      Author: Omar Makke(O jMakke)
 *      ojQuote: "If you cannot beat them, write GNU software "
 */

#ifndef RECTIFY_HPP_
#define RECTIFY_HPP_

#include "activation.h"
#include <math.h>

template <typename T>
class  Rectify : public Activation<T>
{
public:
	T f(T fnet)
	{
		if((double) fnet < 0.0)
		{
			return (T) 0.0;
		}
		return (T) fnet;
	}
	/**
	 *  Derivative. T will be casted double and back from double
	 *   */
	T df(T fnet)
	{
		if((double) fnet == 0.0)
		{
			return (T) 0.0;
		}
		return (T) 1.0;
	}
	~Rectify<T>(){}
};



#endif /* RECTIFY_HPP_ */
