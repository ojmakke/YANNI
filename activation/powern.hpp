/*
 * powern.hpp
 *
 *  Created on : Mar 17, 2016
 *      Author : Omar Makke (O jMakke)
 *      ojQuote: "The quality of code is inversely proportional
 *      	  to the temperature outside."
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

#ifndef POWERN_HPP_
#define POWERN_HPP_

#include "activation.h"
#include <math.h>

template <typename T>
class  PowerN : public Activation<T>
{
public:
  static int N;
  PowerN()
  {
    N_ = N++;
  }
  /* <T> is casted to double and then back to <T> */
  T f(T fnet)
  {
    y = (T) pow(fnet, N_);
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
    if(N_ == (T) 0) return (T) 0;

    return (T) ((T) N_)*y/((T) N_);
  }
  ~PowerN<T>(){}

private:
  int N_;
  T fnet_old;
  T y;
};

template<typename T>
int PowerN<T>::N = 0;

template class PowerN<double>;
template class PowerN<float>;
#endif /* POWERN_HPP_ */
