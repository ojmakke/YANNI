/*
 * step.hpp
 *
 *  Created on : Mar 17, 2016
 *      Author : Omar Makke (Omar jMakke)
 *      ojQuote: "Freedom of speech? More like freedom to impeach!"
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
