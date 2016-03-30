/*
 * fullhidden.h
 *
 *  Created on : Mar 19, 2016
 *      Author : Omar Makke (O jMakke)
 *      ojQutoe: "One day generations will look back
 *      		  and thank the founding hackers"
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

#ifndef NETWORKS_FULLHIDDEN_H_
#define NETWORKS_FULLHIDDEN_H_

#include "classic_network.h"
#include "../parts/layer.h"
#include "../activation/activation.h"
#include "../activation/tanh.hpp"

template<typename T>
class FullHidden
{
public:
  /* Note: hidden_layers can be 0
         * layer_count: Number of layers which must be >= 2.
         * It includes hidden and output
         * *layers: Array for the size of each layer.
         */
  FullHidden();
  FullHidden(size_t *layers,
             size_t layer_count,
             ActivationEnum *swtiching_functions);
  ~FullHidden();

  /*
         * Default training (incremental).
         * Returns error achieved after end of training
         */
  static int id;
  T train(struct Classic_Dataset<T> *training_data);
  T train(struct Classic_Dataset<T>  *training_data,
          T target_error,
          T epoch,
          T learning_rate);
  void forward_propagate();
  // Assumed to be equal to all_layers - 1, due to bias
  void set_inputs(T *inputs);
  void dump_everything();
  void dump_outputs();
  void dump_layer(size_t n);
  // size will be assumed to equal the output layer.
  T calc_error(T *target);

private:
  void back_propagate(T rate);
  void update_weights(T rate);
  std::vector<Layer<T> *> all_layers;
  T learning_rate;
};

#endif /* NETWORKS_FULLHIDDEN_H_ */
