/*
 * node.cpp
 *
 *  Created on : Mar 17, 2016
 *      Author : Omar Makke (O jMakke)
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

#include <vector>

#include "node.h"
#include "node_phantom.h"
#include "edge.h"
#include "activation/activation.h"
#include "activation/logistic.hpp"
#include "activation/step.hpp"
#include "activation/rectify.hpp"
#include "activation/tanh.hpp"
#include "activation/fixedinput.hpp"
#include "activation/powern.hpp"
#include "helper/nnhelper.hpp"
#include "common.h"


extern NNHelper<double> nnhelper;

template<typename T>
Node<T>::Node(ActivationEnum type):
  Node_Phantom<T>(),
  y_(this->y),
  fnet_(this->fnet),
  delta_(this->delta)
{
  is_input=false;
  is_output=false;
  this->delta = (T) 0.0;
  switch(type)
    {
    case LOGISTIC:
      {
        F =  new Logistic<T>();
        break;
      }
    case TANH:
      {
        F = new Tanh<T>();
        break;
      }
    case RECTIFY:
      {
        F = new Rectify<T>();
        break;
      }
    case STEP:
      {
        F = new Step<T>();
        break;
      }
    case FIXEDINPUT:
      {
        F = new FixedInput<T>();
        break;
      }
    case POWERN:
      {
	F = new PowerN<T>();
	break;
      }
    }
}

template<typename T>
Node<T>::~Node()
{
  // Remember, as you see in connectTo(), edges are created in node.
  // Therefore, node clears them.
  // The "Next edge
  if(forward.size() == 0)
    {

    }
  else
    {
      for(size_t i = 0; i < forward.size(); i++)
        {
          Edge<T> *edge = forward.at(i);
          delete(edge);
        }
    }
  delete F;
}

template<typename T>
void Node<T>::connect_to(Node<T> *node)
{
  // Create an edge
  Edge<T> *edge = new Edge<T>();

  edge->set_value((T) nnhelper.randomizer.get_rand());
  edge->set_next(node);
  edge->set_prev(this);

  // Store the edge in both nodes
  forward.push_back(edge);

  // This node is behind the next node
  std::vector<Edge<T> *> *backward = &(node->backward);
  backward->push_back(edge);
  return;
}

template<typename T>
void Node<T>::reset_backward_weights()
{
  if(is_input) return;
  for(size_t ii = 0; ii < backward.size(); ii++)
    {
      Edge<T> *edge_ii = backward.at(ii);
      edge_ii->reset_weight();
    }
}

template<typename T>
void Node<T>::set_output(T output)
{
  this->y = output;
}

// TODO ask molecule
template<typename T>
void Node<T>::req_output(T output)
{
  set_output(output);
}

//TODO
// Abstract calculation method to allow parallel computing
// Add dirty flag to avoid re-calculation if nothing has changed.
// Dirty flag will go into the node and is set when edge states are updated
template<typename T>
T Node<T>::calc_new_output()
{
  // Input doesn't have input edges.
  if(is_input)
    {
      return y_;
    }

  this->fnet = (T) 0.0;
  // Loop through all edges
  for(size_t i = 0; i < backward.size(); i++)
    {
      Edge<T> *i_edge = backward.at(i);
      // previous node connecting to current node through the edge
      const Node<T>* i_node = i_edge->p_;
      this->fnet += i_edge->value_ * i_node->y_;
    }
  this->y = F->f(this->fnet);
  return (T) this->y;	// Optional. Doesn't have to be used.
}

template<typename T>
T Node<T>::calc_new_output_test()
{
  // Input doesn't have input edges.
  if(is_input)
    {
      return y_;
    }

  this->fnet = (T) 0.0;
  // Loop through all edges
  for(size_t i = 0; i < backward.size(); i++)
    {
      Edge<T> *i_edge = backward.at(i);
      // previous node connecting to current node through the edge
      const Node<T>* i_node = i_edge->p_;
      if(i_edge->get_value_test() == i_edge->value_)
	{
	  int breakp = 0;
	  breakp++;
	}
      else
	{
	  int breakp = 0;
	  breakp++;
	}
      this->fnet += i_edge->get_value_test() * i_node->y_;
    }
  this->y = F->f(this->fnet);
  return (T) this->y;	// Optional. Doesn't have to be used.
}

template<typename T>
void Node<T>::set_delta(T _delta)
{
  this->delta = _delta;
}

//TODO ask molecule
template<typename T>
void Node<T>::req_delta(T _delta)
{
  set_delta(_delta);
}

// Tell compiler which classes to compile
template class Node<double>;
template class Node<float>;
