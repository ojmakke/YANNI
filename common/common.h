/*
 * common.h
 *
 *  Created on : Mar 17, 2016
 *      Author : Omar Makke (O jMakke)
 *      ojQuote: "Hacking is surgery while cracking is robbery"
 *
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


#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <memory>

typedef enum NNResult_def
{
  NNERROR,
  NNOK,
  NNUNKNOWN,
} NNResult;

typedef struct NNInfo_def
{
  struct std::unique_ptr<struct NNInfo_def> stack;
  std::string message;
  NNResult result;
} NNInfo;

typedef std::unique_ptr<NNInfo> NNInfo_uptr;
#define MAKE_NNINFO(T) NNInfo_uptr T(new NNInfo)

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define LEAVE_ON_ERROR(T) if(T->result == NNERROR) return T;

// String constants
namespace MSG
{
  const std::string FILE_NOT_FOUND = "File Not Found\n";
  const std::string FILE_OPEN_ERR = "Error opening file\n";
  const std::string DIM_ERROR = "Incorrect dimensions\n";
  const std::string INIT_ERROR = "Not Initialized\n";
  const std::string LAYER_SIZE_ERROR = "Incorrect input layer size\n";
  const std::string INPUT_ERROR = "Incorrect value in input\n";
  const std::string FILE_MISMATCH = "File/Network dimension mismatch\n";
}
NNInfo_uptr default_info();
void append_info(NNInfo_uptr& info);
std::string extract_release_error(NNInfo_uptr& info);

#endif // COMMON_H
