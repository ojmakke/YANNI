/*
 * classic_network.cpp
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

const std::string NETSIZE = "Must have at least 3 layers";
const std::string LAYERSIZE = "Incorrect layer size";
const std::string NOFUNCTION = "Layer needs function";
const std::string BADFUNCTION = "Invalid activation function";

NNInfo_uptr classic_network(
    const Parser& parser,
    std::vector<FullHidden<double> *>& nets)
{
  NNInfo_uptr ret = default_info();

  size_t layers = parser.p_size;
  if(layers < 3)
    {
      ret->result = NNERROR;
      ret->message = NETSIZE;
      return ret;
    }
  // loop to make sure structure is good
  for(size_t ii = 0; ii < layers; ii++)
    {
      if(atoi(parser.parameters[ii]->command.c_str()) < 1)
	{
	  ret->result = NNERROR;
	  ret->message = LAYERSIZE;
	  return ret;
	}
      // All but input need activation function
      // Below checks are not for the input layer, skip.
      if(ii == 0) { continue; }

      if(parser.parameters[ii]->p_size != 1)
	{
	  ret->result = NNERROR;
	  ret->message = NOFUNCTION;
	  return ret;
	}
      // get switching function
      std::string sf = parser.parameters[ii]->parameters[0]->command;
      if(    sf.compare(FUNCS::TANH) != 0
	  && sf.compare(FUNCS::LOGISTIC) != 0
	  && sf.compare(FUNCS::POWERN) != 0
	  && sf.compare(FUNCS::RECTIFY) != 0)
	{
	  ret->result = NNERROR;
	  ret->message = BADFUNCTION;
	  return ret;
	}
    }
  // Up to here, good. Create
  size_t *layers_size = new size_t[layers];
  ActivationEnum *switching = new ActivationEnum[layers];
  for(size_t ii = 0; ii < layers; ii++)
    {
      layers_size[ii] = atoi(parser.parameters[ii]->command.c_str());
      // below do not apply for i = 0 (input layer)
      if(ii == 0){ continue; }
      // get switching function
      std::string sf = parser.parameters[ii]->parameters[0]->command;
      if(sf.compare(FUNCS::TANH) == 0)
	{
	  switching[ii] = TANH;
	}
      else if(sf.compare(FUNCS::LOGISTIC) == 0)
	{
	  switching[ii] = LOGISTIC;
	}
      else if(sf.compare(FUNCS::RECTIFY) == 0)
	{
	  switching[ii] = RECTIFY;
	}
    }
  FullHidden<double> *network =
      new FullHidden<double>(layers_size, layers, switching);
  nets.push_back(network);
  ret->result = NNOK;

  delete[] layers_size;
  delete[] switching;

  return ret;
//  ConsolePrinter::instance().network_write_nets(networks);

}

