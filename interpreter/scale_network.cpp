/*
 * scale_network.cpp
 *
 *  Created on : Apr 24, 2016
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

#include <string>
#include <vector>

#include "common.h"
#include "networks/fullhidden.h"
#include "parser.h"

const std::string NOTREADY = "Network not initialized.";
const std::string WRONGINPUT = "Error. scale(value_in, value_out)";
const std::string RANGEERROR = "Incorrect scale value.";
const std::string INPUTERROR = "Error in input";

NNInfo_uptr scale_network(
    const Parser& parser,
    FullHidden<double>* const net)
{
  NNInfo_uptr ret = default_info();
  size_t params = parser.p_size;
  if(params != 2)
	{
	  ret->message = WRONGINPUT;
	  ret->result = NNERROR;
	  return ret;
	}
  if(parser.parameters == nullptr)
    {
      ret->message = INPUTERROR;
      ret->result = NNERROR;
      return ret;
    }

  net->input_scale = atof(parser.parameters[0]->command.c_str());
  if(net->input_scale == 0.0)
    {
      ret->message = RANGEERROR;
      ret->result = NNERROR;
      return ret;
    }

  net->output_scale = atof(parser.parameters[1]->command.c_str());
  if(net->output_scale == 0.0)
    {
      ret->message = RANGEERROR;
      ret->result = NNERROR;
      return ret;
    }

  ret->result = NNOK;
  return ret;
}
