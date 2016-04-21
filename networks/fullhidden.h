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
#include <memory>

template<typename T>
class FullHidden
{
public:
  const size_t& input_layer_size_;
  const size_t& output_layer_size_;

  /* Note: hidden_layers can be 0
         * layer_count: Number of layers which must be >= 2.
         * It includes hidden and output
         * *layers: Array for the size of each layer.
         */
  int self_id;
  FullHidden();
  FullHidden(size_t *layers,
             size_t layer_count,
             ActivationEnum *swtiching_functions);
  virtual ~FullHidden();

  /*
         * Default training (incremental).
         * Returns error achieved after end of training
         */
  static int id;
  T train();
  T train(T target_error,
	  T epoch,
	  T learning_rate,
	  double dropoff);
  void forward_propagate();
  // Assumed to be equal to all_layers - 1, due to bias
  void set_inputs(T *inputs);
  void dump_everything();
  void dump_outputs();
  void dump_layer(size_t n);
  std::unique_ptr<T[]> get_output();
  // size will be assumed to equal the output layer.
  T calc_error(T *target);
  //TODO move to interface
  void input_file_alloc(std::string filename);
  void output_file_alloc(std::string filename);
  bool input_allocated;
  bool output_allocated;

protected:
  T** input_set; // Tripple because allocation happens in function.
                  // The reference is passed by value :)
  T** output_set;
  size_t input_layer_size;
  size_t output_layer_size;

  // these are not the dimension of the input. These are the dimension of
  // the traiing set
  size_t data_in_length;
  size_t data_out_length;
  virtual void back_propagate(T rate);
  virtual void update_weights(T rate);
  virtual void forward_propagate_test();
  std::vector<Layer<T> *> all_layers;
  T learning_rate;
  T error_now;
  T previous_error;
};

#endif /* NETWORKS_FULLHIDDEN_H_ */
