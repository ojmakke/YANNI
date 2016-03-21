/*
 * gnunet_test.cpp
 *
 *  Created on: Mar 19, 2016
 *      Author: Omar Makke (O jMakke)
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "activation/tanh.hpp"
#include "activation/logistic.hpp"
#include "activation/step.hpp"
#include "activation/rectify.hpp"
#include "helper/nnhelper.hpp"
#include "networks/fullhidden.h"


float** construct_2d(const size_t X, const size_t Y)
{
	float **pointer;
	pointer = new float*[50]; // dynamic `array (size 4) of pointers to int`
	fprintf(stdout, "First D\n");
	for (size_t i = 0; i < X; i++)
	{
		fprintf(stdout, "2nd D\n");
	  	pointer[i] = new float[Y];
	}
	return pointer;
}

void delete_2d(float **pointer, const float X)
{
	for (size_t i = 0; i < X; ++i)
	{
	  delete[] pointer[i];
	}
	delete[] pointer;
}

void run_tests()
{
//	fprintf(stdout, "Creating 1x1x1 network\n");
//	size_t size = 3;
//	size_t layers[] = {1, 1, 1};
//	ActivationEnum switching[] = {TANH, LOGISTIC, STEP};
//	size_t *l;
//	l = layers;
//	FullHidden<double> s(l, size, switching);
//	fprintf(stdout, "Creation of 1x1x1 network complete\n");
//	s.dump_everything();

//	fprintf(stdout, "Creating 10x10x10 network\n");
//
//	size = 5;
//	size_t layers3[] = {3, 3, 3, 3, 3};
//	float inputs3[] = {0.3, 0.8, -0.1};
//	ActivationEnum switching3[] = {TANH, LOGISTIC, TANH, TANH, TANH};
//	FullHidden<float> s3(layers3, size, switching3);
//	s3.set_inputs(inputs3);
////	s3.dump_everything();
//	fprintf(stdout, "Current outputs1 are:\n");
//	s3.dump_outputs();
//	s3.forward_propagate();
//	fprintf(stdout, "Current outputs2 are:\n");
//	s3.dump_outputs();
//	inputs3[0] = 0.1f; inputs3[1] = 0.1f; inputs3[2] = -0.5f;
//	s3.set_inputs(inputs3);
//
////	s3.dump_everything();
//	fprintf(stdout, "Current outputs3 are:\n");
//	s3.forward_propagate();
//	s3.dump_outputs();


	fprintf(stdout, "Creating 2D arrays:\n");
	float **input;
	float **desired;
	const size_t X = 20;
	const size_t Y1 = 1;
	const size_t Y2 = 2;
	input = construct_2d(X, Y1);
	desired = construct_2d(X, Y2);


//	input = new float*[X]; // dynamic `array (size 4) of pointers to int`
//	fprintf(stdout, "First D\n");
//	for (size_t i = 0; i < X; i++)
//	{
//		fprintf(stdout, "2nd D\n");
//	  	input[i] = new float[Y];
//	}

	fprintf(stdout, "Initializing:\n");
	for(size_t i = 0; i < X; i++)
	{
		for(size_t j = 0; j < Y1; j++)
		{
			fprintf(stdout, "Writing:\n");
			input[i][j] = ((float) i*5.1f)/50.0f;
		}
	}
	fprintf(stdout, "Initializing desired:\n");
	for(size_t i = 0; i < X; i++)
	{

		desired[i][0] = (float) sin(((float) i*5.1f)/10.0f);
		desired[i][1] = (float) cos(((float) i*5.1f)/10.0f);
	}

	__training_struct<float> data_struct;
	data_struct.input_set = input;
	data_struct.target_set = desired;

	data_struct.x = X;
	fprintf(stdout, "Looping:\n");
	for(size_t i = 0; i < X; i++)
		fprintf(stdout, "Value is %f, %f, %f\n",
				(float) data_struct.input_set[i][0],
				data_struct.target_set[i][0],
				data_struct.target_set[i][1]);



	fprintf(stdout, "Creating 1x10x1 network\n");

	size_t size = 3;
	size_t layers3[] = {1, 10, 1};

	ActivationEnum switching3[] = {TANH, TANH, TANH};
	FullHidden<float> s3(layers3, size, switching3);

	float error = s3.train(&data_struct, 0.001f, 10000, 0.15f);
	fprintf(stdout, "Achieved %f error\n", error);

	float test = 15.1f;
	s3.set_inputs(&test);
	s3.forward_propagate();
	s3.dump_outputs();

	fprintf(stdout, "values should be close to %f, %f\n", sin(test), cos(test));

	delete_2d(input, X);
	delete_2d(desired, X);



	//FullHidden<double> smallest(layers, size);
	//smallest.dump_everything();
}

