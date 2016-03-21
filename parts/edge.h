/*
 * edge.h
 *
 *  Created on: Mar 17, 2016
 *      Author: Omar Makke ( OJ )
 *      ojQuote: "The hardest thing about Mathematics is truly understanding the definitions"
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
	bool is_connected;	// For dropoff, i.e. assume not connected.

public:
	Edge();
	Edge(T value);
	void set_value(T edge_value);
	T get_value();
	Node<T> *n;	// Link to next nodes
	Node<T> *p;	// Link to previous node.

};


#endif /* PARTS_EDGE_H_ */
