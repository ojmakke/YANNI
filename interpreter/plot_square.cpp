/*
 * plot_square.cpp
 *
 *  Created on : Apr 24, 2016
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
#include <string>
#include <vector>

#include "activation/activation.h"
#include "common.h"
#include "networks/fullhidden.h"
#include "activation/activation.h"
#include "parser.h"
#include "Images/bmp_handler.h"


const std::string NOT2D = "Input or output is not 2D";
const std::string NOTREADY = "Network not initialized.";
const std::string INPUTERROR = "Error in input";
const std::string WRONGRANGE = "Wrong range.";

NNInfo_uptr plot_square(
    const Parser& parser,
    FullHidden<double>* const net)
{
  NNInfo_uptr ret = default_info();
  size_t params = parser.p_size;

  if(params != 3
      || net->output_layer_size_ != 1
      || net->input_layer_size_ != 2)
    {
      ret->result = NNERROR;
      ret->message = INPUTERROR;
      return ret;
    }

  if(parser.parameters == nullptr)
    {
      ret->result = NNERROR;
      ret->message = INPUTERROR;
      return ret;
    }

  // Format is plotSquare(begin,step,end)
  for(size_t ii = 0; ii < 3; ii++)
    {
      if(parser.parameters[ii] == nullptr)
	{
	  ret->result = NNERROR;
	  ret->message = INPUTERROR;
	  return ret;
	}
    }

  double xp0 = atof(parser.parameters[0]->command.c_str());
  double xp1 = atof(parser.parameters[1]->command.c_str());
  double xp2 = atof(parser.parameters[2]->command.c_str());

  if(abs(xp2 - (xp0 + xp1)) > abs(xp2 - xp0))
    {
      ret->result = NNERROR;
      ret->message = WRONGRANGE;
      return ret;

    }

  if(net == nullptr)
    {
      ret->result = NNERROR;
      ret->message = NOTREADY;
      return ret;
    }

  //TODO find a way to compare against expression
  // Finally we know input is good
  size_t img_size = (size_t) (xp2-xp0)/xp1;
  if(img_size > 5000)	// prevent mistake: ridiculous image size
    {
      img_size = 5000;
    }

  BMPInfo *pixels = new BMPInfo[img_size*img_size];
  std::unique_ptr<double[]> out;
  double input[2];
  for(size_t ii = 0; ii < img_size; ii++)
    {
      for(size_t jj = 0; jj < img_size; jj++)
	{
	  input[0] = ((double) ii)/((double) img_size);
	  input[1] = ((double) jj)/((double) img_size);
	  net->set_inputs(input);
	  net->forward_propagate();
	  out = net->get_output();
	  if(out[0] > 0.5) out[0] = 1.0; else out[0] = 0.0;
	  pixels[ii*img_size + jj].color[0] = 255*fabs(out[0]);
	  pixels[ii*img_size + jj].color[1] = 0;
	  pixels[ii*img_size + jj].color[2] = 0;
	  pixels[ii*img_size + jj].x = jj;
	  pixels[ii*img_size + jj].y = img_size - ii - 1;
	}
    }
  create_square_bmp("output.bmp", pixels, img_size*img_size, img_size);
  delete[] pixels;
  ret->result = NNOK;
  return ret;
}

