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
  fprintf(stdout, "Creating 2D arrays:\n");
  float **input;
  float **desired;
  const size_t X = 40;
  const size_t Y1 = 1;
  const size_t Y2 = 2;
  input = construct_2d(X, Y1);
  desired = construct_2d(X, Y2);

  fprintf(stdout, "Initializing:\n");
  for(size_t i = 0; i < X; i++)
    {
      for(size_t j = 0; j < Y1; j++)
        {
          fprintf(stdout, "Writing:\n");
          input[i][j] = ((float) i*3.1f)/X;
        }
    }
  fprintf(stdout, "Initializing desired:\n");
  for(size_t i = 0; i < X; i++)
    {
      desired[i][0] = (float) sin(((float) i*3.1f)/X);
      desired[i][1] = (float) cos(((float) i*3.1f)/X);
    }

  struct Classic_Dataset <float> data_struct;
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
  size_t layers3[] = {1, 150, 2};

  ActivationEnum switching3[] = {TANH, TANH,TANH};
  FullHidden<float> s3(layers3, size, switching3);

  float error = s3.train(&data_struct, 0.11f, 10500, 0.00251f);
  fprintf(stdout, "Achieved %f error\n", error);


  for(size_t i = 0; i < X; i++)
    {
      s3.set_inputs(input[i]);
      s3.forward_propagate();
   //   s3.dump_outputs();
  //    fprintf(stdout, "values should be close to %f, %f\n",
  //            desired[i][0],
   //       desired[i][1]);
    }


  delete_2d(input, X);
  delete_2d(desired, X);



  //FullHidden<double> smallest(layers, size);
  //smallest.dump_everything();
}

