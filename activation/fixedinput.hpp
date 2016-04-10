/*
 * fixedinput.hpp
 *
 *  Created on : Mar 17, 2016
 *      Author : Omar Makke (O jMakke)
 *      ojQuote: "Programming is a science while coding is an art"
 *    	Email  : ojmakke@yahoo.com

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

