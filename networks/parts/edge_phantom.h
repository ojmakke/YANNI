/*
 * edge_phantom.h
 *
 *  Created on: Apr 3, 2016
 *      Author: Omar Makke ( OJ )
 *      ojQuote: "Soon the government will legalize pointer exceptions"
 *      Email  : ojmakke@yahoo.com

This file is part of "Yet Another Neural Nets Implementation",
also known as YANNI

YANNI is free software: you can redistribute it and/or modify
it under the terms of the Affero GNU General Public License as published by
the Free Software Foundation, version 3 of the License.

YANNI is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the Affero
GNU General Public License for more details.

You should have received a copy of the Affero GNU General Public License
along with YANNI.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef EDGE_PHANTOM_H
#define EDGE_PHANTOM_H


// Friend of inheritor
// Makes friends of of the inheritor only see protected :)
template<typename T>
class Node;

template<typename T>
class Edge;

template<typename T>
class Edge_Phantom
{
  friend class Edge<T>;
private:
  // This is for internal use of edge.
  // For dropoff, i.e. assume not connected.
  bool is_connected;

  // Value assigned to the edge
  T value;
  T new_value;

  // Value used by the edge, seen by the world
  // Exeriment: Attempting to minimize methods.
  // Attempting to get rid of get_value()..
  T effective_value;	// dropoff value = 0

  // Nodes know about these.
  Node<T> *n;	// Link to next nodes
  Node<T> *p;	// Link to previous node.

public:
  Edge_Phantom(){}
};

#endif // EDGE_PHANTOM_H
