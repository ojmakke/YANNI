/*
 * randomizer.cpp
 *
 *  Created on: Mar 17, 2016
 *      Author: Omar Makke
 */
#ifndef RANDOMIZER_H_
#define RANDOMIZER_H_

template<typename T>
class Randomizer
{
public:
	Randomizer();
	T getRand(T in, T max);
	T getRand();		// Between 0 and 1

};

#endif /* RANDOMIZER_H_ */




