/*
 * classic_network.h
 *
 *  Created on : Apr 25, 2016
 *      Author : Omar Makke (O jMakke)
 *      ojQuote: "Why do we program? To preserve freedom"
 *      Email  : ojmakke@yahoo.com

This file is part of "Yet Another Neural Nets Implementation",
also known as YANNI

YANNI is free software: you can redistribute it and/or modify
it under the terms of the Affero GNU General Public License as published by
the Free Software Foundation, version 3 of the License.

YANNI is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the Affero
GNU General Public License for more details.

You should have received a copy of the Affero GNU General Public License
along with YANNI.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef NETWORKS_FEATURE_NET_H_
#define NETWORKS_FEATURE_NET_H_

#include <vector>

#include "fullhidden.h"

template<typename T>
class Feature_Net: public FullHidden<T>
{
  std::vector<FullHidden<T> *> *input_nets;
  FullHidden<T> *output_net;
public:
  // these nets should already be constructed
  Feature_Net();
  Feature_Net(std::vector<FullHidden<T> *> *input_nets__,
	      FullHidden<T> *output_net__);

  T train(T target_error,
	  T epoch,
	  T learning_rate,
	  double dropoff);
  T retrain();
  void set_inputs(T *inputs);
  virtual void reset_weights();
  virtual void forward_propagate();
  //  virtual void dump_layer(size_t n);
  virtual std::unique_ptr<T[]> get_output();
  // size will be assumed to equal the output layer.
  virtual T calc_error(T *target);

};



#endif /* NETWORKS_FEATURE_NET_H_ */
