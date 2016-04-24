/*
 * fullhidden.cpp
 *
 *  Created on : Mar 19, 2016
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

#include <stdlib.h>
#include <stdio.h>
#include <memory>

#include "common.h"
#include "parts/edge.h"
#include "parts/node.h"
#include "parts/layer.h"
#include "taylornet.h"

void clear_2d(double** data, size_t dim);
void clear_2d(float** data, size_t dim);

template<typename T>
TaylorNet<T>::TaylorNet():FullHidden<T>()
{
}

/**
 * layers: array containing the size of each layer
 * layer_count: How many layers, i.e, layers size and switching functions size
 */
template<typename T>
TaylorNet<T>::TaylorNet(size_t *layers,
			size_t layer_count):FullHidden<T>()
{
  this->input_layer_size = layers[0];
  this->output_layer_size = layers[layer_count-1];

  // Create layers and make last layer output,and first layer input
  for(size_t i = 0; i < layer_count; i++)
    {
      // Reset the exponent
      PowerN<T>::N = 1;
      Layer<T> *i_layer;

      // only last layer is POWERN
      if(i == 1)
	{
	  i_layer = new Layer<T>(layers[i], POWERN);
	}
      else
	{
	  i_layer = new Layer<T>(layers[i], TANH);
	}

      if(i == 0) // make input
        {
          for(size_t j = 0; j < layers[i]; j++)
            {
              Node<T> *j_node = (i_layer->nodes).at(j);
              j_node->is_input = true;
            }
        }
      else if(i == layer_count - 1)
        {
          for(size_t j = 0; j < layers[i]; j++)
            {
              Node<T> *j_node = (i_layer->nodes).at(j);
              j_node->is_output = true;
            }
        }
      this->all_layers.push_back(i_layer);
    }

  // Create bias nodes as input.
  for(size_t i = 0; i < layer_count-1; i++)
    {
      Layer<T> *i_layer = this->all_layers.at(i);
      i_layer->add_bias();
    }

  // connect the layers
  for(size_t i = 0; i < layer_count-1; i++)
    {
      Layer<T> *i_layer = this->all_layers.at(i);
      Layer<T> *i_next_layer = this->all_layers.at(i+1);
      i_layer->connect_to(*i_next_layer);
    }
}

template<typename T>
TaylorNet<T>::~TaylorNet()
{
}

// Tell compiler which classes will be used
template class TaylorNet<double>;
template class TaylorNet<float>;
