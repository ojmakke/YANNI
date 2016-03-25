/*
 * edge.h
 *
 *  Created on: Mar 17, 2016
 *      Author: Omar Makke ( OJ )
 *      ojQuote: "The hardest thing about Mathematics is
 *       		  truly understanding the definitions"
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
