/*
 * classic_network.h
 *
 *  Created on : Mar 19, 2016
 *      Author : Omar Makke (O jMakke)
 *      ojQuote: "When it doubt, fprintf out"
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

#ifndef CLASSIC_NETWORK_H
#define CLASSIC_NETWORK_H

template<typename T>
struct Classic_Dataset
{
  size_t x;		// y matches layer size
  T **input_set;
  T **target_set;
};

template<typename T>
class ClassicParams
{
public:
  T target_error;
  T epoch;
  T learning_rate;
  ClassicParams();
  ClassicParams(T __target_error, T __epoch, T __learning_rate);
};


template<typename T>
class ClassicNetwork
{
public:

  /*
   * Default training (incremental).
   * Returns error achieved after end of training
   */
  virtual T train() = 0;
  virtual void forward_propagate() = 0;
  // Assumed to be equal to all_layers - 1, due to bias
  virtual void set_inputs(T *inputs) = 0;
  virtual void get_outputs(T* out_you_allocate) = 0;
  // size will be assumed to equal the output layer.
  virtual T calc_error(T *target) = 0;
  virtual void learn(T rate) = 0;
  virtual ~ClassicNetwork(){}
};

#endif // CLASSIC_NETWORK_H
