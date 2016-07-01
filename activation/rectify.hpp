/*
 * rectify.hpp
 *
 *  Created on : Mar 17, 2016
 *      Author : Omar Makke(O jMakke)
 *      ojQuote: "If you cannot beat them, write GNU software "
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
//    if((double) fnet < 0.0)
//      {
//        return (T) 0.0;
//      }
    return (T) fnet;
  }
  /**
         *  Derivative. T will be casted double and back from double
         *   */
  T df(T fnet)
  {
    if((double) fnet == 0.0)
      {
//        return (T) 0.0;
      }
    return (T) 1.0;
  }
  ~Rectify<T>(){}
};

template class Rectify<double>;
template class Rectify<float>;

#endif /* RECTIFY_HPP_ */
