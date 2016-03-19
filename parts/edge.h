/*
 * edge.h
 *
 *  Created on: Mar 17, 2016
 *      Author: Omar Makke
 */

#ifndef PARTS_EDGE_H_
#define PARTS_EDGE_H_

template<typename T>
class Node;

template<typename T>
class Edge
{
private:
	T value;
	bool isConnected;	// For dropoff, i.e. assume not connected.

public:
	Edge();
	Edge(T value);
	void setValue(T edge_value);
	T getValue();
	Node<T> *n;	// Link to next nodes
	Node<T> *p;	// Link to previous node.
};


#endif /* PARTS_EDGE_H_ */
