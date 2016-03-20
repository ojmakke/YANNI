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
	 * Default training
	 */
	T train();
	T train(T target_error, T epoch, T learning_rate);
	void dump_everything();


private:
	std::vector<Layer<T> *> all_layers;

};



#endif /* NETWORKS_FULLHIDDEN_H_ */
