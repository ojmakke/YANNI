/*
 * retrain_network.cpp
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

NNInfo_uptr retrain_network(
    const Parser& parser,
    FullHidden<double>* const net)
{
  NNInfo_uptr ret = default_info();

  if(   net == nullptr
     || net->input_allocated == false
     || net->output_allocated == false)
    {
      ret->message = NOTREADY;
      ret->result = NNERROR;
      return ret;
    }

  net->retrain();
  ret->result = NNOK;
  return ret;
}
