/*
 * node.h
 *
 *  Created on : Mar 17, 2016
 *      Author : Omar Makke (O jMakke)
 *		ojQuote: "Either live free, or code trying."
 *		Email  : ojmakke@yahoo.com

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
class Edge_Phantom;

template<typename T>
class Node_Phantom
{
  // Trick to make friends only access protected!
};

template<typename T>
class Node : Node_Phantom<T>
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
  T get_output() const;
  T get_net();
  T calc_new_output(); // Calculates new output from input
  // (forward propagation);
  void set_output(T output);
  /*
         * This will modify next nodes edge "backward" vector,
         * and this->forward edge vector
         */
  void connect_to(Node *next_node);
  T get_delta() const;
  void set_delta(T delta);	// for output neurons

private:
  T y;
  T fnet;
  T delta;
};



#endif /* PARTS_NODE_H_ */
