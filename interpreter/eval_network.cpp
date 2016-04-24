/*
 * eval_network.cpp
 *
 *  Created on : Apr 24, 2016
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

#include <string>
#include <vector>

#include "activation/activation.h"
#include "common.h"
#include "networks/fullhidden.h"
#include "activation/activation.h"
#include "parser.h"

const std::string NOTREADY = "Network not initialized.";
const std::string WRONGINSIZE = "Input doesn't match network's input";
const std::string INPUTERROR = "Error in input";

NNInfo_uptr eval_network(
    const Parser& parser,
    FullHidden<double>* const current_net)
{
  NNInfo_uptr ret = default_info();
  size_t params = parser.p_size;

  if(   current_net == nullptr
     || current_net->input_allocated == false
     || current_net->output_allocated == false)
    {
      ret->result = NNERROR;
      ret->message = NOTREADY;
      return ret;
    }

  if(params  != current_net->input_layer_size_)
    {
      ret->result = NNERROR;
      ret->message = WRONGINSIZE;
      return ret;
    }

  if(parser.parameters == nullptr)
    {
      ret->result = NNERROR;
      ret->message = INPUTERROR;
      return ret;
    }
  if(   current_net == nullptr
     || current_net->input_allocated == false
     || current_net->output_allocated == false)
    {
      ret->result = NNERROR;
      ret->message = NOTREADY;
      return ret;
    }

  double *in = new double[parser.p_size];
  for(size_t ii = 0; ii < parser.p_size; ii++)
    {
      in[ii] = atof(parser.parameters[ii]->command.c_str())/current_net->input_scale;
    }

  current_net->set_inputs(in);
  current_net->forward_propagate();

  ret->result = NNOK;
  return ret;
}


