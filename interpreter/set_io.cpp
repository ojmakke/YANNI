/*
 * set_io.cpp
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

const std::string PARAMERROR = "Input takes 1 parameter only";
const std::string INPUTERROR = "Error in input";
const std::string NOACTIVENET = "No activate networks. use(net#)";

NNInfo_uptr set_io(
    const Parser& parser,
    const std::vector<FullHidden<double> *>& nets,
    FullHidden<double>* const current_net)
{
  NNInfo_uptr ret = default_info();
  size_t params = parser.p_size;
  if(params  != 2)
    {
      ret->result = NNERROR;
      ret->message = INPUTERROR;
      return ret;
    }
  if(parser.parameters == nullptr)
    {
      ret->result = NNERROR;
      ret->message = INPUTERROR;
      return ret;
    }
  if(current_net == nullptr)
    {
      ret->result = NNERROR;
      ret->message = NOACTIVENET;
      return ret;
    }

  ret = current_net->input_file_alloc(parser.parameters[0]->command);
  if(ret->result != NNOK)
    {
      // get the final message result
      ret->message = "Error reading input file";
      ret->message += extract_release_error(ret->stack);
      ret->stack.release();
      ret->stack = nullptr;
      return ret;
    }

  ret = current_net->output_file_alloc(parser.parameters[1]->command);
  if(ret->result != NNOK)
    {
      // get the final message result
      ret->message = "Error reading output file";
      ret->message += extract_release_error(ret->stack);
      ret->stack.release();
      ret->stack = nullptr;
      return ret;
    }

  ret->result = NNOK;
  return ret;
}

