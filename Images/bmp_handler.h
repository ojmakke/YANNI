/*
 * bmp_handler.h
 *
 *  Created on : Apr 12, 2016
 *      Author : Omar Makke (O jMakke)
 *      ojQuote: "Good universities don't make good students.
 *      	  Good students make good universities"
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

#ifndef BMP_HANDLER_H_
#define BMP_HANDLER_H_

#include <string.h>
#include "EasyBMP.h"

typedef struct BMPInfo_def
{
  int x;
  int y;
  double color[3];	// RGB
} BMPInfo;

void create_square_bmp(std::string filename,
		const BMPInfo* bmp_color,
		size_t info_length,
		size_t side_length);

#endif /* BMP_HANDLER_H_ */
