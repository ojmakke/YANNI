/*
 * logistic.hpp
 *
 *  Created on : Mar 17, 2016
 *      Author : Omar Makke (O jMakke)
 *      ojQuote: "Freedom is like a bootloader.
 *      		  Without it, we cannot operate."
 *      Email  : ojmakke@yahoo.com

This file is part of GNU Nets also known as GNUNets

GNU Nets is free software: you can redistribute it and/or modify
it under the terms of the Affero GNU General Public License as published by
the Free Software Foundation, version 3 of the License.

GNU Nets is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the Affero
GNU General Public License for more details.

You should have received a copy of the Affero GNU General Public License
along with GNU Nets.  If not, see <http://www.gnu.org/licenses/>.
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
		if(y > (T) 0.995)
		{
			y = (T) 0.995;
		}
		else if(y < (T) -0.995)
		{
			y = (T) -0.995;
		}
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
			y = f(fnet);
		}
		return (T) y*(1.0-y);
	}
	~Logistic<T>(){}

private:
	T fnet_old;
	T y;
};

template class Logistic<double>;
template class Logistic<float>;
#endif /* LOGISTIC_HPP_ */
