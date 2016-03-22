/*
 * layer.h
 *
 *  Created on : Mar 18, 2016
 *      Author : Omar Makke
 *      ojQuote: "When odds are against me, I make my own statistics"
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

#ifndef PARTS_LAYER_H_
#define PARTS_LAYER_H_

#include <vector>
#include <stdlib.h>

#include "edge.h"
#include "../activation/activation.h"
#include "../activation/logistic.hpp"
#include "../activation/tanh.hpp"

template<typename T>
class Layer
{
public:
	 Layer(size_t size, ActivationEnum switching_function);
	~Layer();
	// Full connection. Each neuron will connect with every neuron
	void connect_to(Layer<T> &next_layer);

	// Get layout outputs in a vector. This is useful mostly for output layer
	std::vector<T> get_layer_outputs();

// Sets the outputs of the neurons. This will make the neurons the "input"
// This will affect back propagation. The errors will not be propagated
// beyond the input arrays.
// Hey! You can fix inputs in some middle layer! How about that!
	int fix_layer_inputs(T *input_array);

// Same as set_layer_inputs, but instead selectively fix some of the inputs.
// Why? MOA INTELLIGENCE. This is not in the research literature yet. It is
// in the GNU literature, as of today :)
	int fix_some_layer_inputs(T *input_array_values,
							  size_t *input_array_index,
							  size_t input_size);
	std::vector<Node<T> *> nodes;

	void add_bias(); // Adds a bias to the layer.
	void calc_node_delta();


private:

};




#endif /* PARTS_LAYER_H_ */
