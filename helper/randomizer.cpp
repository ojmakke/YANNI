/*
 * randomizer.cpp
 *
 *  Created on : Mar 17, 2016
 *      Author : Omar Makke
 *      Email  : ojmakke@yahoo.com

This file is part of "Yet Another Neural Nets Implementation",
also known as YANNI

YANNI is free software: you can redistribute it and/or modify
it under the terms of the Affero GNU General Public License as published by
the Free Software Foundation, version 3 of the License.

YANNI is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the Affero
GNU General Public License for more details.

You should have received a copy of the Affero GNU General Public License
along with YANNI.  If not, see <http://www.gnu.org/licenses/>.
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
T Randomizer<T>::get_rand()
{
  srand(time(0));
  return ((T) rand())/((T) RAND_MAX);
}

template<typename T>
T Randomizer<T>::get_rand(T min, T max)
{
  return ( ((T) rand())/((T) RAND_MAX) * (max - min) + min);
}

// force instantiation
template class Randomizer<double>;
template class Randomizer<float>;
template class Randomizer<int>;
