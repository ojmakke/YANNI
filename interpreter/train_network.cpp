/*
 * train_network.cpp
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

const std::string BADPARAM = "Error. Use train(error,epoch,rate, drop%)";
const std::string NOTREADY = "Network not initialized.";
const std::string OUTOFRANGE = "Parameters are out of range";

NNInfo_uptr train_network(
    const Parser& parser,
    FullHidden<double>* const current_net)
{
  NNInfo_uptr ret = default_info();

  size_t params = parser.p_size;
  if(params  != 3 && params != 4)
    {
      ret->message = BADPARAM;
      ret->result = NNERROR;
      return ret;
    }
  if(parser.parameters == nullptr)
    {
      ret->message = BADPARAM;
      ret->result = NNERROR;
      return ret;
    }
  if(   current_net == nullptr
     || current_net->input_allocated == false
     || current_net->output_allocated == false)
    {
      ret->message = NOTREADY;
      ret->result = NNERROR;
      return ret;
    }
  double error = atof(parser.parameters[0]->command.c_str());
  unsigned int epoch = atoi(parser.parameters[1]->command.c_str());
  double rate = atof(parser.parameters[2]->command.c_str());
  double dropoff = 0.0;
  if(params == 4)
    {
      dropoff = atof(parser.parameters[3]->command.c_str());
    }
  if(error < 0.0 || rate < 0.0000000001 || epoch > 500000
     || dropoff < 0.0 || dropoff >  0.99 )
    {
      ret->message = OUTOFRANGE;
      ret->result = NNERROR;
      return ret;
    }

  current_net->train(error, epoch, rate, dropoff);
  ret->result = NNOK;
  return ret;
}
