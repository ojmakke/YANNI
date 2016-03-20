/*
 * randomizer.cpp
 *
 *  Created on: Mar 17, 2016
 *      Author: Omar Makke (O jMakke)
 *      ojQuote: "Every person needs some personal philosophy in life"
 */
#ifndef RANDOMIZER_H_
#define RANDOMIZER_H_

template<typename T>
class Randomizer
{
public:
	Randomizer();
	T get_rand(T in, T max);
	T get_rand();		// Between 0 and 1

};

#endif /* RANDOMIZER_H_ */




