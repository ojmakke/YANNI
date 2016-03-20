/*
 * activation.h
 *
 *  Created on: Mar 17, 2016
 *      Author: Omar Makke (O jMakke)
 *      ojQuote: "Young man, listen carefully to the gray hair."
 */

#ifndef ACTIVATION_H_
#define ACTIVATION_H_

/** Activation function abstract structure */
template<typename T>
class Activation
{
public:
	virtual T f(T fnet) = 0;
	virtual T df(T fnet) = 0;

	virtual ~Activation() = 0;
};

template<typename T>
Activation<T>::~Activation()
{
}

enum ActivationEnum
{
	LOGISTIC,
	RECTIFY,
	STEP,
	TANH,
};

// Tell compiler which classes to build
template class Activation<double>;
template class Activation<float>;

#endif /* ACTIVATION_H_ */
