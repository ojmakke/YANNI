/*
 * gnunets.cpp
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

#include <string.h>
#include <stdlib.h>
#include <iostream>

#include "activation/tanh.hpp"
#include "activation/logistic.hpp"
#include "activation/step.hpp"
#include "activation/rectify.hpp"
#include "helper/nnhelper.hpp"
#include "helper/console_printer.h"
#include "networks/fullhidden.h"

#define CONTROL 0
#define INPUT 1

NNHelper<double> nnhelper;

int main(int argc, char* argv[])
{
  // Experimental use of singletons. This singleton changes console's global state.
  // Might be dangerous and confusing. Let us see.
  ConsolePrinter::instance().interact();
//  double **indata, **outdata;

//  unsigned int in_length = FileIO<T>::get_text_1D("../logicinput.txt", 2, &indata);
//  unsigned int out_length = FileIO<T>::get_text_1D("../logicoutput.txt",1, &outdata);

//  struct Classic_Dataset <double> data_struct;
//  data_struct.input_set = indata;
//  data_struct.target_set = outdata;
//  data_struct.x = in_length;
//  size_t size = 4;
//  size_t layers3[] = {2, 3,3, 1};

//  ActivationEnum switching3[] = {TANH, TANH,TANH, TANH};
//  FullHidden<double> s3(layers3, size, switching3);

//  float error = s3.train(&data_struct, 0.001f, 120000, 0.0151f);
//  std::string result = "Achieved error: ";
//  result.append(std::to_string(error));
//  ConsolePrinter::instance().feedback_write(result);

//  {
//  double testin[] = {0.3, 0.21};
//  s3.set_inputs(testin);
//  s3.forward_propagate();
//  s3.dump_outputs();
//  }
//  {
//  double testin[] = {0.7, 0.3};
//  s3.set_inputs(testin);
//  s3.forward_propagate();
//  s3.dump_outputs();
//  }
//  {
//  double testin[] = {0.7, 0.7};
//  s3.set_inputs(testin);
//  s3.forward_propagate();
//  s3.dump_outputs();
//  }
//  {
//  double testin[] = {0.3, 0.7};
//  s3.set_inputs(testin);
//  s3.forward_propagate();
//  s3.dump_outputs();
//  }
//  while(1);



  // Apply state machine.
  // control: keys are for control, not inputting command
  // input: RELEVANT keys are used for inputting.
}

