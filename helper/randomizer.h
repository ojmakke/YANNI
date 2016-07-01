/*
 * randomizer.h
 *
 *  Created on : Mar 17, 2016
 *      Author : Omar Makke (O jMakke)
 *      ojQuote: "Every person needs some personal philosophy in life"
 *      Email  : ojmakke@yahoo.com

This file is part of GNU Nets also known as GNUNets

GNU Nets is free software: you can redistribute it and/or modify
it under the terms of the Affero GNU General Public License as published by
the Free Software Foundation, version 3 of the License.

GNU Nets is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the Affero
GNU General Public License for more details.

You should have received a copy of the Affero GNU General Public License
along with GNU Nets.  If not, see <http://www.gnu.org/licenses/>.
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



