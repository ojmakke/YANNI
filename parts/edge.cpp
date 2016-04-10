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
#include "node.h"
#include "../helper/nnhelper.hpp"

extern NNHelper<double> nnhelper;

template<typename T>
void Edge<T>::set_value(T edge_value)
{
  if(this->is_connected)
    {
      this->value = edge_value;
      this->effective_value = this->value;
    }
}

template<typename T>
void Edge<T>::set_drop_off(bool state)
{
  this->is_connected = !state;
  if(this->is_connected)
    {
      this->effective_value = this->value;
    }
  else
    {
      this->effective_value = (T) 0.0;
    }
}

//TODO ask molecule
template<typename T>
void Edge<T>::req_drop_off(bool state)
{
  set_drop_off(state);
}

//TODO ask molecule
template<typename T>
void Edge<T>::req_rand_drop_off(T percentage)
{
  if(percentage < (T) 0.0 || percentage > (T) 0.99)
    {
      return;
    }
  if(this->p->is_input)
    {
      return;
    }
  T v = nnhelper.randomizer.get_rand();
  if(v < (T) percentage)
    {
      set_drop_off(true);
    }
  else
    {
      set_drop_off(false);
    }
}



template<typename T>
void Edge<T>::req_value(T edge_value)
{
  //TODO: Ask molecule
  set_value(edge_value);
}

template<typename T>
Edge<T>::Edge():value_(this->effective_value)
{
  this->p = nullptr;
  this->n = nullptr;
  p_ = this->p;
  n_ = this->n;
  this->is_connected = true;
  set_value(nnhelper.randomizer.get_rand());
}

template<typename T>
Edge<T>::Edge(T v):value_(this->effective_value)
{
  this->p = nullptr;
  this->n = nullptr;
  p_ = this->p;
  n_ = this->n;
  this->value = v;
  this->is_connected = true;
}

template<typename T>
void Edge<T>::set_next(Node<T> * const next)
{
  this->n = next;
  n_ = this->n;
}

template<typename T>
void Edge<T>::set_prev(Node<T> * const prev)
{
  this->p = prev;
  p_ = this->p;
}

// Tell compiler what to build
template class Edge<double>;
template class Edge<float>;
