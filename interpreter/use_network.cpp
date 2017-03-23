/*
 * use_network.cpp
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

const std::string WRONGPARAM = "use takes 1 parameter only";
const std::string INPUTERROR = "Error in input";
const std::string NETNOTFOUND = "Network is not found";

bool activate_network(int net_id,
		      const std::vector<FullHidden<double> *>& nets,
		      FullHidden<double>* &current_net);

NNInfo_uptr use_network(
    const Parser& parser,
    const std::vector<FullHidden<double> *>& nets,
    FullHidden<double>* &current_net)
{
  NNInfo_uptr ret = default_info();

  size_t params = parser.p_size;
  if(params  != 1)
    {
      ret->result = NNERROR;
      ret->message = WRONGPARAM;
      return ret;
    }
  if(parser.parameters == nullptr)
    {
      ret->result = NNERROR;
      ret->message = INPUTERROR;
      return ret;
    }
  int id = atoi(parser.parameters[0]->command.c_str());
  if(!activate_network(id, nets, current_net))
    {
      ret->result = NNERROR;
      ret->message = NETNOTFOUND;
      return ret;
    }
  ret->result = NNOK;
  return ret;
}

bool activate_network(int net_id,
		      const std::vector<FullHidden<double> *>& nets,
		      FullHidden<double>* &current_net)
{
  for(size_t ii = 0; ii < nets.size(); ii++)
    {
      if(nets.at(ii)->self_id == net_id)
        {
          current_net = nets.at(ii);
          return true;
        }
    }
  return false;
}

