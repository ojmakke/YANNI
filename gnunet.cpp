/*
 * gnunet.cpp
 *
 *  Created on: Mar 17, 2016
 *      Author: Omar Makke
 */
#include <iostream>

#include "activation/tanh.hpp"
#include "activation/logistic.hpp"
#include "activation/step.hpp"
#include "activation/rectify.hpp"
#include "helper/nnhelper.hpp"

 NNHelper<double> nnhelper;

int main(int argc, char* argv[])
{

	Tanh<double> f;
	std::cout<<f.f(1.0)<<" "<<f.df(1.0);


	return 0;
}

