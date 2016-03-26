/*
 * gnunet.cpp
 *
 *  Created on: Mar 17, 2016
 *      Author: Omar Makke (O jMakke)
 */

#include <string.h>
#include <stdlib.h>

#include "activation/tanh.hpp"
#include "activation/logistic.hpp"
#include "activation/step.hpp"
#include "activation/rectify.hpp"
#include "helper/nnhelper.hpp"
#include "helper/console_printer.h"

#define CONTROL 0
#define INPUT 1

NNHelper<double> nnhelper;
extern void run_tests();

void switch_state(unsigned *state);

int main(int argc, char* argv[])
{
  // Experimental use of singletons. This singleton changes console's global state.
  // Might be dangerous and confusing. Let us see.
  ConsolePrinter::instance().interact();

  // Apply state machine.
  // control: keys are for control, not inputting command
  // input: RELEVANT keys are used for inputting.
}


