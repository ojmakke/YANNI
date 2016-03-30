/*
 * workspace.cpp
 *
 *  Created on : Mar 26, 2016
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

#include "workspace.h"
#include "console_printer.h"
#include "../networks/fullhidden.h"
#include "../activation/activation.h"

extern void run_tests();

Workspace::Workspace()
{
}

Workspace& Workspace::instance()
{
  static Workspace ws;
  return ws;
}

void Workspace::execute(Parser &parser)
{
  if(parser.command.compare("demo") == 0)
    {
      ConsolePrinter::instance().feedback_rewrite(
            "Starting Demo...                   ");
      run_tests();
    }
  // classic network
  else if(parser.command.compare("cn")==0)
    {
      size_t layers = parser.p_size;
      if(layers < 3)
        {
          ConsolePrinter::instance().feedback_rewrite(
                "Must have at least 3 layers    ");
          return;
        }
      // loop to make sure structure is good
      for(size_t ii = 0; ii < layers-1; ii++)
        {
          if(atoi(parser.parameters[ii]->command.c_str()) < 1)
            {
              ConsolePrinter::instance().feedback_rewrite(
                    "Incorrect layer size       ");
              return;
            }
          if(parser.parameters[ii]->p_size != 1)
            {
              ConsolePrinter::instance().feedback_rewrite(
                    "Layer needs a function    ");
              return;
            }
          // get switching function
          std::string sf = parser.parameters[ii]->parameters[0]->command;
          if(sf.compare("tanh") != 0 && sf.compare("logistic") != 0)
            {
              ConsolePrinter::instance().feedback_rewrite(
                    "Invalid function          ");
              return;
            }
        }
      // Up to here, good. Create
      size_t *layers_size = new size_t[layers];
      ActivationEnum *switching = new ActivationEnum[layers];
      for(size_t ii = 0; ii < layers-1; ii++)
        {
          layers_size[ii] = atoi(parser.parameters[ii]->command.c_str());
          // get switching function
          std::string sf = parser.parameters[ii]->parameters[0]->command;
          if(sf.compare("tanh") == 0)
            {
              switching[ii] = TANH;
            }
          else
            {
              switching[ii] = LOGISTIC;
            }
        }
      FullHidden<double> *network =
          new FullHidden<double>(layers_size, layers, switching);
      networks.push_back(network);
      ConsolePrinter::instance().network_write_nets(networks);

      delete[] layers_size;
      delete[] switching;
    }
  else
    {
      std::string result = "Unrecognized command: ";
      result.append(parser.command).append(". Try demo");
      ConsolePrinter::instance().feedback_rewrite(result);
    }
}

void Workspace::activate_network(int net_id)
{
  for(size_t ii = 0; ii < networks.size(); ii++)
    {
      if(networks.at(ii)->id == net_id)
        {
          current_network = networks.at(ii);
        }
    }
}

Workspace::~Workspace()
{
  for(size_t ii = 0; ii < networks.size(); ii++)
    {
      delete networks.at(ii);
    }
}
