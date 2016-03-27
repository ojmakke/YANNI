/*
 * activation.h
 *
 *  Created on : Mar 17, 2016
 *      Author : Omar Makke (O jMakke)
 *      ojQuote: "Young man, listen carefully to the gray hair."
 *
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

#ifndef ACTIVATION_H_
#define ACTIVATION_H_

/** Activation function abstract structure */
template<typename T>
class Activation
{
public:
  virtual T f(T fnet) = 0;
  virtual T df(T fnet) = 0;

  virtual ~Activation() = 0;
};

template<typename T>
Activation<T>::~Activation()
{
}

enum ActivationEnum
{
  LOGISTIC,
  RECTIFY,
  STEP,
  TANH,
  FIXEDINPUT,
};

// Tell compiler which classes to build
template class Activation<double>;
template class Activation<float>;

#endif /* ACTIVATION_H_ */
