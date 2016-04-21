/*
 * fullhidden.h
 *
 *  Created on : Mar 19, 2016
 *      Author : Omar Makke (O jMakke)
 *      ojQutoe: "Software bugs and hell are similar. Painful, punishing,
 *      	  and you cannot prove they don't exist"
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

#ifndef TAYLORNET_H_
#define TAYLORNET_H_

#include "classic_network.h"
#include "../parts/layer.h"
#include "../activation/activation.h"
#include "fullhidden.h"
#include "../activation/powern.hpp"
#include <memory>

template<typename T>
class TaylorNet : public FullHidden<T>
{
public:
  TaylorNet();
  TaylorNet(size_t *layers,
             size_t layer_count);
  ~TaylorNet();
};

#endif /* TAYLORNET_H_ */
