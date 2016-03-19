/*
 * node.h
 *
 *  Created on: Mar 17, 2016
 *      Author: Omar Makke
 */

#ifndef PARTS_NODE_H_
#define PARTS_NODE_H_

#include <vector>
#include <stdlib.h>

#include "../activation/activation.h"

template<typename T>
class Edge;

template<typename T>
class Node
{
public:
	Activation<T> F;

	std::vector<Edge<T> *> forward;  // Forward Edges. Normally only 1 edge
	std::vector<Edge<T> *> backward; // Backward edges

//	Node(size_t outputs, size_t inputs, ActivationEnum type);
	Node(ActivationEnum type);
	~Node();
	void connectTo(Node *node);

private:
	T y;
	T fnet;
};



#endif /* PARTS_NODE_H_ */
