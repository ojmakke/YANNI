/*
 * console_printer.cpp
 *
 *  Created on : Apr 12, 2016
 *      Author : Omar Makke (O jMakke)
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

#include <string.h>
#include <stdlib.h>

#include "bmp_handler.h"


void create_square_bmp(std::string filename,
		const BMPInfo* bmp_color,
		size_t info_length,
		size_t side_length)
{
  BMP out;
  if(side_length < 0) return;
  if(side_length > 2048) return;
  out.SetSize(side_length, side_length);
  out.SetBitDepth(24);

  // Set white background
  RGBApixel w_pixel;
  w_pixel.Alpha = 0;
  w_pixel.Blue = 255;
  w_pixel.Green = 255;
  w_pixel.Red = 255;

  for(size_t ii = 0; ii < side_length; ii++)
    for(size_t jj = 0; jj < side_length; jj++)
      {
	out.SetPixel(ii,jj, w_pixel);
      }

  // write the pixels
  for(size_t ii = 0; ii < info_length; ii++)
    {
      RGBApixel pixel;
      pixel.Alpha = 0;
      pixel.Blue = bmp_color[ii].color[2];
      if(pixel.Blue < 0 || pixel.Blue > 255) pixel.Blue = 0;

      pixel.Green = bmp_color[ii].color[1];
      if(pixel.Green < 0 || pixel.Green > 255) pixel.Green = 0;

      pixel.Red = bmp_color[ii].color[0];
      if(pixel.Red < 0 || pixel.Red > 255) pixel.Red = 0;

      out.SetPixel(bmp_color[ii].x, bmp_color[ii].y, pixel);
    }

  out.WriteToFile(filename.c_str());
}


