/*
 * fullhidden.h
 *
 *  Created on: Mar 19, 2016
 *      Author: Omar Makke (O jMakke)
 *      ojQutoe: "One day generations will look back and thank the founding hackers"
 */

#ifndef NETWORKS_FULLHIDDEN_H_
#define NETWORKS_FULLHIDDEN_H_

#include "../parts/layer.h"
#include "../activation/activation.h"
#include "../activation/tanh.hpp"

template<typename T>
struct __training_struct
{
	size_t x;		// y matches layer size
	T **input_set;
	T **target_set;
};

template<typename T>
class FullHidden
{
public:
	/* Note: hidden_layers can be 0
	 * layer_count: Number of layers which must be >= 2. It includes hidden and output
	 * *layers: Array for the size of each layer.
	 */
	FullHidden();
	FullHidden(size_t *layers, size_t layer_count, ActivationEnum *swtiching_functions);
	~FullHidden();

	/*
	 * Default training (incremental).
	 * Returns error achieved after end of training
	 */
	T train(__training_struct<T> *training_data);
	T train(__training_struct<T>  *training_data, T target_error, T epoch, T learning_rate);
	void forward_propagate();
	// Assumed to be equal to all_layers - 1, due to bias
	void set_inputs(T *inputs);
	void dump_everything();
	void dump_outputs();
	void dump_layer(size_t n);
	T calc_error(T *target);	// size will be assumed to equal the output layer.


private:
	void back_propagate(T rate);
	void update_weights(T rate);
	std::vector<Layer<T> *> all_layers;
	T learning_rate;
};

#endif /* NETWORKS_FULLHIDDEN_H_ */
