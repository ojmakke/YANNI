/*
 * validate_network.cpp
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
#include "fileio/fileio.h"

const std::string BADPARAM = "Error. Use validate(inputfile,outputfile)";
const std::string NOTREADY = "Network not initialized.";
const std::string OUTOFRANGE = "Parameters are out of range";

double** construct_2d(const size_t rows, const size_t cols);
void delete_2d(double **pointer, const double rows);

NNInfo_uptr validate_network(
    const Parser& parser,
    FullHidden<double>* const net)
{
  NNInfo_uptr ret = default_info();

  if(   net == nullptr
     || net->input_allocated == false
     || net->output_allocated == false)
    {
      ret->message = NOTREADY;
      ret->result = NNERROR;
      return ret;
    }

  if( parser.p_size != 2)
    {
      ret->message = BADPARAM;
      ret->result = NNERROR;
      return ret;
    }

  if( parser.parameters[0] == nullptr || parser.parameters[1] == nullptr)
    {
      ret->message = BADPARAM;
      ret->result = NNERROR;
      return ret;
    }

  std::string inputfile = parser.parameters[0]->command;
  std::string outputfile = parser.parameters[1]->command;

  FileIO::Table inputs;
  size_t data_len;
  ret = FileIO::get_text_1D(inputfile, net->input_layer_size_,
			    &inputs.data, &inputs.rows);

  if(ret->result != NNOK)
    {
      return ret;
    }

  FileIO::Table outputs;
  outputs.data = construct_2d(inputs.rows, net->output_layer_size_);
  outputs.rows = inputs.rows;
  outputs.cols = net->output_layer_size_;
  // Input and output are generated.
  // Loop through input. Feedforward, get the output.
  // Then store.
  for(size_t ii = 0; ii < inputs.rows; ii++)
    {
      double* in_vector = inputs.data[ii];
      for(size_t jj = 0; jj < inputs.cols; jj++)
	{
	  in_vector[jj] /= net->input_scale;
	}
      net->set_inputs(in_vector);
      net->forward_propagate();
      outputs.data[ii] = net->get_output().release();

      for(size_t jj = 0; jj < outputs.cols; jj++)
	{
	  outputs.data[ii][jj] *= net->output_scale;
	}
    }
  delete_2d(inputs.data, inputs.rows);

  ret = FileIO::write_csv(outputfile, outputs);
  if(ret->result != NNOK)
    {
      return ret;
    }
  delete_2d(outputs.data, outputs.rows);
  ret->result = NNOK;
  return ret;
}

// rows are the "input vectors" because that is how the files are created.
double** construct_2d(const size_t rows, const size_t cols)
{
  double **pointer;
  pointer = new double*[rows]; // dynamic `array (size 4) of pointers to int`
  for (size_t ii = 0; ii < rows; ii++)
    {
      pointer[ii] = new double[cols];
    }
  return pointer;
}

void delete_2d(double **pointer, const double rows)
{
  for (size_t ii = 0; ii < rows; ++ii)
    {
      delete[] pointer[ii];
    }
  delete[] pointer;
}
