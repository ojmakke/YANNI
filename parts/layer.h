/*
 * layer.h
 *
 *  Created on: Mar 18, 2016
 *      Author: Omar Makke
 */

#ifndef PARTS_LAYER_H_
#define PARTS_LAYER_H_

#include <vector>

#include "edge.h"

template<typename T>
class Layer
{
public:
	Layer(int size);
	~Layer();
	void connectTo(Layer<T> layer);

private:


};




#endif /* PARTS_LAYER_H_ */
