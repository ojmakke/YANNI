/*
 * workspace.cpp
 *
 *  Created on : Mar 26, 2016
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
#include <string.h>
#include <memory>
#include <cmath>

#include "common.h"
#include "interpreter/commands.h"
#include "workspace.h"

#include "console_printer.h"
#include "networks/fullhidden.h"
//#include "activation/activation.h"
#include "interpreter/parser.h"

extern void run_tests();

Workspace::Workspace():hasStarted(false)
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
 //     run_tests();
      return;
    }
  // classic network
  else if(parser.command.compare("cn") == 0)
    {
      NNInfo_uptr ret = classic_network(parser, networks);

      if(ret->result == NNOK)
	{
	  ConsolePrinter::instance().network_write_nets(networks);
	}
      else
	{
	  ConsolePrinter::instance().feedback_rewrite(ret->message);
	}
      return;
    }

  else if(parser.command.compare("use") == 0)
    {
      NNInfo_uptr ret = use_network(parser, networks, current_network);
      if(ret->result == NNOK)
	{
	  ConsolePrinter::instance().network_write_active(current_network);
	}
      else
	{
	  ConsolePrinter::instance().feedback_rewrite(ret->message);
	}
      return;
    }

  else if(parser.command.compare("set_io") == 0)
    {
      NNInfo_uptr ret = set_io(parser, networks, current_network);
      if(ret->result == NNOK)
	{
	  ConsolePrinter::instance().feedback_rewrite("Input and Output loaded");
	}
      else
	{
	  ConsolePrinter::instance().feedback_rewrite(ret->message);
	}
      return;
    }

  else if(parser.command.compare("train") == 0)
    {
      NNInfo_uptr ret = train_network(parser, current_network);
      if(ret->result != NNOK)
	{
	  ConsolePrinter::instance().feedback_rewrite(ret->message);
	}

      return;
    }

  else if(parser.command.compare("eval") == 0)
    {
      NNInfo_uptr ret = eval_network(parser, current_network);
      if(ret->result != NNOK)
	{
	  ConsolePrinter::instance().feedback_rewrite(ret->message);
	}
      else
	{
	  std::unique_ptr<double[]> out = current_network->get_output();

	  size_t out_len = current_network->output_layer_size_;

	  // TODO:
	  // Do not output from here.
	  for(size_t ii = 0; ii < out_len; ii++)
	    {
	      std::string outstr = "Output ";
	      double val = out[ii]*current_network->output_scale;
	      outstr.append(std::to_string(ii))
	          .append(": Value: ")
	          .append(std::to_string(val));

	      ConsolePrinter::instance().feedback_write(outstr);
	    }
	}
      return;
    }

  else if(parser.command.compare("exit") == 0)
    {
      abort();
    }

  else if(parser.command.compare("scale") == 0)
    {
      NNInfo_uptr ret = scale_network(parser, current_network);
      if(ret->result != NNOK)
	{
	  ConsolePrinter::instance().feedback_rewrite(ret->message);
	}
      else
	{
	  ConsolePrinter::instance().feedback_rewrite("Scales set");
	}
      return;
    }
  else if(parser.command.compare("plotSquare") == 0)
    {
   //   NNInfo_uptr ret = plot_square(parser, current_network);
   //   if(ret->result != NNOK)
//	{
//	  ConsolePrinter::instance().feedback_rewrite(ret->message);
//	}
//      else
//	{
//	  ConsolePrinter::instance().feedback_rewrite("Plot complete");
//	}
      return;
    }

  else if(parser.command.compare("reset") == 0)
    {
      NNInfo_uptr ret = reset_network(parser, current_network);
      if(ret->result != NNOK)
	{
	  ConsolePrinter::instance().feedback_rewrite(ret->message);
	}
      else
	{
	  ConsolePrinter::instance().feedback_rewrite("Weights are reset");
	}
      return;
    }
  else if(parser.command.compare("retrain") == 0)
    {
      NNInfo_uptr ret = retrain_network(parser, current_network);
      if(ret->result != NNOK)
	{
	  ConsolePrinter::instance().feedback_rewrite(ret->message);
	}
      return;
    }
  else if(parser.command.compare("validate") == 0)
    {
      NNInfo_uptr ret = validate_network(parser, current_network);
      if(ret->result != NNOK)
	{
	  ConsolePrinter::instance().feedback_rewrite(ret->message);
	}
      else
	{
	  ConsolePrinter::instance().feedback_rewrite("Output file written");
	}
      return;
    }

  else
    {
      std::string result = "Unrecognized command: ";
      result.append(parser.command).append(". Try demo");
      ConsolePrinter::instance().feedback_rewrite(result);
    }
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
