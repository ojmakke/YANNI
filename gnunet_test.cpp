/*
 * gnunet_test.cpp
 *
 *  Created on: Mar 19, 2016
 *      Author: Omar Makke (O jMakke)
 */

#include <stdlib.h>
#include <stdio.h>

#include "activation/tanh.hpp"
#include "activation/logistic.hpp"
#include "activation/step.hpp"
#include "activation/rectify.hpp"
#include "helper/nnhelper.hpp"
#include "networks/fullhidden.h"

void run_tests()
{
	fprintf(stdout, "Creating 1x1x1 network\n");
	size_t size = 3;
	size_t layers[] = {1, 1, 1};
	ActivationEnum switching[] = {TANH, LOGISTIC, STEP};
	size_t *l;
	l = layers;
	FullHidden<double> s(l, size, switching);
	fprintf(stdout, "Creation of 1x1x1 network complete\n");
	s.dump_everything();

	fprintf(stdout, "Creating 10x10x10 network\n");

	size = 3;
	size_t layers10[] = {10, 10, 10};
	FullHidden<float> s10(layers10, size, switching);
	s10.dump_everything();

	//FullHidden<double> smallest(layers, size);
	//smallest.dump_everything();

}

