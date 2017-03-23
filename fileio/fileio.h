/*
 * fileio.h
 *
 *  Created on : Mar 28, 2016
 *      Author : Omar Makke (O jMakke)
 *      ojQuote: "The the programming tool ever is coffee"
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

#ifndef FILEIO_H_
#define FILEIO_H_

#include <fstream>
#include <iostream>
#include <string.h>

#include "common.h"

#define DELIMITER ','

namespace FileIO
{
  typedef struct Table_def
  {
    size_t rows = 0;
    size_t cols = 0;
    double** data = nullptr;
  } Table;

  unsigned int char_count(std::string string, char c);

  // This also modifies the string and returns the rest
  // Gets first entry in a delimited line, modifies string to remaining line
  std::string get_first_entry(std::string *str, char d);

  NNInfo_uptr get_text_1D(std::string filename,
                             unsigned int dimension,
                             double*** you_own_data,
			     size_t *line_count_o);

  // Write comma delimited table
  NNInfo_uptr write_csv(std::string filename, const Table data);
}

#endif /* FILEIO_H_ */

