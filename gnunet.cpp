/*
 * gnunet.cpp
 *
 *  Created on: Mar 17, 2016
 *      Author: Omar Makke (O jMakke)
 */
#include <iostream>

#include "activation/tanh.hpp"
#include "activation/logistic.hpp"
#include "activation/step.hpp"
#include "activation/rectify.hpp"
#include "helper/nnhelper.hpp"

NNHelper<double> nnhelper;

extern void run_tests();

int main(int argc, char* argv[])
  {
    run_tests();
    fprintf(stdout, "Tests complete");
    return 0;
  }

