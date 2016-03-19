/*
 * randomizer.cpp
 *
 *  Created on: Mar 17, 2016
 *      Author: Omar Makke
 */

#include <random>
#include <ctime>
#include <cstdlib>

#include "randomizer.h"

template<typename T>
Randomizer<T>::Randomizer()
{
	srand(time(0));
}

template<typename T>
T Randomizer<T>::getRand()
{
	return ((T) rand())/((T) RAND_MAX);
}

template<typename T>
T Randomizer<T>::getRand(T min, T max)
{
	return 	( ((T) rand())/((T) RAND_MAX) * (max - min) + min);
}

// force instentiation
template class Randomizer<double>;
template class Randomizer<float>;
template class Randomizer<int>;
