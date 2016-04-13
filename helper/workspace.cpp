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
#include <string.h>
#include <memory>

#include "workspace.h"
#include "console_printer.h"
#include "../networks/fullhidden.h"
#include "../activation/activation.h"

extern void run_tests();

Workspace::Workspace():hasStarted(false),input_scale(1.0),output_scale(1.0)
{
  current_network = nullptr;
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
      return;
    }
  // classic network
  else if(parser.command.compare("cn") == 0)
    {
      size_t layers = parser.p_size;
      if(layers < 3)
        {
          ConsolePrinter::instance().feedback_rewrite(
                "Must have at least 3 layers    ");
          return;
        }
      // loop to make sure structure is good
      for(size_t ii = 0; ii < layers; ii++)
        {
          if(atoi(parser.parameters[ii]->command.c_str()) < 1)
            {
              ConsolePrinter::instance().feedback_rewrite(
                    "Incorrect layer size       ");
              return;
            }
          // All but input need activation function
          // Below checks are not for the input layer, skip.
          if(ii == 0) { continue; }

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
      for(size_t ii = 0; ii < layers; ii++)
        {
          layers_size[ii] = atoi(parser.parameters[ii]->command.c_str());
          // below do not apply for i = 0 (input layer)
          if(ii == 0){ continue; }
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

  else if(parser.command.compare("use") == 0)
    {
      size_t params = parser.p_size;
      if(params  != 1)
        {
          ConsolePrinter::instance().feedback_rewrite(
                "Use takes 1 parmeter only ");
          return;
        }
      if(parser.parameters == nullptr)
        {
          ConsolePrinter::instance().feedback_rewrite(
                "Error in input ");
          return;
        }
      int id = atoi(parser.parameters[0]->command.c_str());
      if(!activate_network(id))
        {
          ConsolePrinter::instance().feedback_rewrite(
                "Network is not found         ");
          return;
        }
      ConsolePrinter::instance().network_write_active(current_network);
      return;
    }

  else if(parser.command.compare("set_io") == 0)
    {
      size_t params = parser.p_size;
      if(params  != 2)
        {
          ConsolePrinter::instance().feedback_rewrite(
                "input takes 1 parmeter only      ");
          return;
        }
      if(parser.parameters == nullptr)
        {
          ConsolePrinter::instance().feedback_rewrite(
                "Error in input           ");
          return;
        }
      if(current_network == nullptr)
        {
          ConsolePrinter::instance().feedback_rewrite(
                "No active networks           ");
          return;
        }
      current_network->input_file_alloc(parser.parameters[0]->command);
      ConsolePrinter::instance().feedback_rewrite(
            "Input loaded...           ");
      current_network->output_file_alloc(parser.parameters[1]->command);
      ConsolePrinter::instance().feedback_rewrite(
            "Output loaded...           ");
      return;
    }

  else if(parser.command.compare("train") == 0)
    {
      size_t params = parser.p_size;
      if(params  != 3 && params != 4)
        {
          ConsolePrinter::instance().feedback_rewrite(
                "train(error,epoch,rate, drop%)          ");
          return;
        }
      if(parser.parameters == nullptr)
        {
          ConsolePrinter::instance().feedback_rewrite(
                "Error in input           ");
          return;
        }
      if(   current_network == nullptr
         || current_network->input_allocated == false
         || current_network->output_allocated == false)
        {
          ConsolePrinter::instance().feedback_rewrite(
                "Network not active and ready           ");
          return;
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
          ConsolePrinter::instance().feedback_rewrite(
                "Invalid training parameters          ");
          return;
        }

      current_network->train(error, epoch, rate, dropoff);
      return;
    }

  else if(parser.command.compare("eval") == 0)
    {
      size_t params = parser.p_size;
      if(   current_network == nullptr
         || current_network->input_allocated == false
         || current_network->output_allocated == false)
        {
          ConsolePrinter::instance().feedback_rewrite(
                "Network not active and ready           ");
          return;
        }

      if(params  != current_network->input_layer_size_)
        {
          ConsolePrinter::instance().feedback_rewrite(
                "wrong input size           ");
          return;
        }
      if(parser.parameters == nullptr)
        {
          ConsolePrinter::instance().feedback_rewrite(
                "Error in input           ");
          return;
        }
      if(   current_network == nullptr
         || current_network->input_allocated == false
         || current_network->output_allocated == false)
        {
          ConsolePrinter::instance().feedback_rewrite(
                "Network not active and ready           ");
          return;
        }

      double *in = new double[parser.p_size];
      for(size_t ii = 0; ii < parser.p_size; ii++)
        {
          in[ii] = atof(parser.parameters[ii]->command.c_str())/input_scale;
        }

      current_network->set_inputs(in);
      current_network->forward_propagate();
      std::unique_ptr<double[]> out = current_network->get_output();

      size_t out_len = current_network->output_layer_size_;

      for(size_t ii = 0; ii < out_len; ii++)
        {
          std::string outstr = "Output ";
          double val = out[ii]*this->output_scale;
          outstr.append(std::to_string(ii))
              .append(": Value: ")
              .append(std::to_string(val));

          ConsolePrinter::instance().feedback_write(outstr);
        }

 //     current_network->dump_outputs();
      return;
    }
  else if(parser.command.compare("exit") == 0)
    {
      abort();
    }
  else if(parser.command.compare("scale") == 0)
    {
      size_t params = parser.p_size;
      if(params != 2)
	{
	  ConsolePrinter::instance().feedback_rewrite(
	      "scale takes 2 parameters                ");
	  return;
	}
      if(parser.parameters == nullptr)
        {
          ConsolePrinter::instance().feedback_rewrite(
                "Error in input           ");
          return;
        }

      input_scale = atof(parser.parameters[0]->command.c_str());
      if(input_scale == 0.0)
	{
	  ConsolePrinter::instance().feedback_rewrite(
	  	      "input scale set to 1                ");
	  input_scale = 1.0;
	}
      output_scale = atof(parser.parameters[1]->command.c_str());
      if(output_scale == 0.0)
	{
	  ConsolePrinter::instance().feedback_rewrite(
	  	      "output scale set to 1                ");
	  output_scale = 1.0;
	}
    }
  else
    {
      std::string result = "Unrecognized command: ";
      result.append(parser.command).append(". Try demo");
      ConsolePrinter::instance().feedback_rewrite(result);
    }
}

bool Workspace::activate_network(int net_id)
{
  for(size_t ii = 0; ii < networks.size(); ii++)
    {
      if(networks.at(ii)->self_id == net_id)
        {
          current_network = networks.at(ii);
          return true;
        }
    }
  return false;
}

void Workspace::start()
{
  if(hasStarted)
    {
      return;
    }
  while(ConsolePrinter::instance().interact());
}

Workspace::~Workspace()
{
  for(size_t ii = 0; ii < networks.size(); ii++)
    {
      delete networks.at(ii);
    }
}
