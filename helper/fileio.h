/*
 * fileio.hpp
 *
 *  Created on : Mar 28, 2016
 *      Author : Omar Makke (O jMakke)
 *      ojQuote: "The the programming tool ever is coffee"
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

#ifndef FILEIO_H
#define FILEIO_H

#include <string>

class FileIO
{
public:

  // reads input, each line is d1, d2, d3, ... where di is the ith dimension
  // dimension is to help the program identify input dimension
  static int get_text_1D(std::string filename,
                         unsigned int dimension,
                         double** you_own_data);
private:
  FileIO();
};

#endif // FILEIO_H
