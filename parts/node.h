/*
 * node.h
 *
 *  Created on: Mar 17, 2016
 *      Author: Omar Makke (O jMakke)
 *		ojQuote: "We all have flaws. Unless of course we change the definition."
 */

#ifndef PARTS_NODE_H_
#define PARTS_NODE_H_

#include <vector>
#include <stdlib.h>

#include "../activation/activation.h"
#include "../activation/logistic.hpp"
#include "../activation/step.hpp"

template<typename T>
class Edge;

template<typename T>
class Node
{
public:

	Activation<T> *F;

	std::vector<Edge<T> *> forward;  // Forward Edges. Normally only 1 edge
	std::vector<Edge<T> *> backward; // Backward edges
	bool is_input;	// Used to mark the neuron as input neuron.
	bool is_output; // Used to mark the neuron as output neuron.

//	Node(size_t outputs, size_t inputs, ActivationEnum type);
	Node(ActivationEnum type);
	~Node();
	T get_output();
	T get_net();
	T calc_new_output(); // Calculates new output from input (forward propagation);
	void set_output(T output);
	/*
	 * This will modify next nodes edge "backward" vector, and this->forward edge vector
	 */
	void connect_to(Node *next_node);
	T get_delta();
	void set_delta(T delta);	// for output neurons

private:
	T y;
	T fnet;
	T delta;
};



#endif /* PARTS_NODE_H_ */
