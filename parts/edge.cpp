/*
 * edge.cpp
 *
 *  Created on : Mar 17, 2016
 *      Author : Omar Makke (O jMakke)
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

#include <random>
#include <cstdlib>
#include <ctime>

#include "edge.h"
#include "../helper/nnhelper.hpp"

extern NNHelper<double> nnhelper;

template<typename T>
T Edge<T>::get_value()
{
  if(this->is_connected)
    {
      return this->value;
    }
  return (T) 0.0;
}

template<typename T>
void Edge<T>::set_value(T edge_value)
{
  if(this->is_connected)
    {
      this->value = edge_value;
    }
  // else do nothing

}

template<typename T>
Edge<T>::Edge()
{
  p = nullptr;
  n = nullptr;
  this->value = nnhelper.randomizer.get_rand();
  this->is_connected = true;
}

template<typename T>
Edge<T>::Edge(T v)
{
  p = nullptr;
  n = nullptr;
  this->value = v;
  this->is_connected = true;
}

// Tell compiler what to build
template class Edge<double>;
template class Edge<float>;
