/*
 * node_phantom.h
 *
 *  Created on : Apr 03, 2016
 *      Author : Omar Makke (O jMakke)
 *		ojQuote: "There are 3 kinds of people:
 *                        the rich, the poor, and the programmers"
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
#ifndef NODE_PHANTOM_H
#define NODE_PHANTOM_H

template<typename T>
class Node;

// Trick; Befriend the inherited. Then friends of the inherited
// can only see protected (not privates) of the inherited
template<typename T>
class Node_Phantom
{
  friend class Node<T>;
private:
  T y;
  T fnet;
  T delta;
};

#endif // NODE_PHANTOM_H
