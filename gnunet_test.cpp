/*
 * gnunet_test.cpp
 *
 *  Created on : Mar 19, 2016
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

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string>

#include "activation/tanh.hpp"
#include "activation/logistic.hpp"
#include "activation/step.hpp"
#include "activation/rectify.hpp"
#include "helper/nnhelper.hpp"
#include "networks/fullhidden.h"
#include "networks/taylornet.h"
#include "helper/console_printer.h"
#include "interpreter/commands.h"

void run_tests()
{
//  fprintf(stdout, "Creating 2D arrays:\n");
  size_t layers_sizes[] = {4,10,10,1};

  ActivationEnum switching[] = {TANH, TANH, TANH, POWERN};

//  FullHidden<double> network(layers_sizes, 4, switching);

  TaylorNet<double> network(layers_sizes, 4);

  network.input_file_alloc("in.csv");
  network.output_file_alloc("o.csv");
  network.reset_weights();
  network.train(0.001,2000,0.000005, 0.0);


  {
  double in[] = {0.2, 0.7};
  network.set_inputs(in);
  network.forward_propagate();
  std::unique_ptr<double[]> out = network.get_output();

  size_t out_len = network.output_layer_size_;

  for(size_t ii = 0; ii < out_len; ii++)
    {
      std::string outstr = "Output ";
      double val = out[ii];
      outstr.append(std::to_string(ii))
                    .append(": Value: ")
		    .append(std::to_string(val));

      ConsolePrinter::instance().feedback_write(outstr);
    }
  }

  {
  double in[] = {0.7, 0.2};
  network.set_inputs(in);
  network.forward_propagate();
  std::unique_ptr<double[]> out = network.get_output();

  size_t out_len = network.output_layer_size_;

  for(size_t ii = 0; ii < out_len; ii++)
    {
      std::string outstr = "Output ";
      double val = out[ii];
      outstr.append(std::to_string(ii))
                    .append(": Value: ")
		    .append(std::to_string(val));

      ConsolePrinter::instance().feedback_write(outstr);
    }
  }

  {
  double in[] = {0.8, 0.8};
  network.set_inputs(in);
  network.forward_propagate();
  std::unique_ptr<double[]> out = network.get_output();

  size_t out_len = network.output_layer_size_;

  for(size_t ii = 0; ii < out_len; ii++)
    {
      std::string outstr = "Output ";
      double val = out[ii];
      outstr.append(std::to_string(ii))
                    .append(": Value: ")
		    .append(std::to_string(val));

      ConsolePrinter::instance().feedback_write(outstr);
    }
  }

  {
  double in[] = {0.1, 0.05};
  network.set_inputs(in);
  network.forward_propagate();
  std::unique_ptr<double[]> out = network.get_output();

  size_t out_len = network.output_layer_size_;

  for(size_t ii = 0; ii < out_len; ii++)
    {
      std::string outstr = "Output ";
      double val = out[ii];
      outstr.append(std::to_string(ii))
                    .append(": Value: ")
		    .append(std::to_string(val));

      ConsolePrinter::instance().feedback_write(outstr);
    }
  }

  while(1);

}

