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

#include "edge_phantom.h"

template<typename T>
class Edge: Edge_Phantom<T>
{
  // This class ecapsulates Node class. Hence it knows about it.
  friend class Node<T>;

protected:
  Edge();
  Edge(T value);
  void set_value(T edge_value);

  // randomizes the edge connection
  void set_drop_off(bool state);
  void set_next(Node<T>* const next);
  void set_prev(Node<T>* const prev);

public:
  // Allow the world to observe.
  const Node<T>* n_;
  const Node<T>* p_;

  // Refernces to the private effective_value;
  // rids of the get_value() (experimental)
  T& value_;

  // Request set value. Not necessarily honored
  void accumulate(T edge_value);
  void confirm_value();
  void undo_value();
  T get_value_test();
  void req_drop_off(bool state);
  void req_rand_drop_off(T percentage);

};


#endif /* PARTS_EDGE_H_ */
