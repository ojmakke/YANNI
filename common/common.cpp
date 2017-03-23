/*
 * common.cpp
 *
 *  Created on : Apr 21, 2016
 *      Author : Omar Makke (O jMakke)
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

#include <string>

#include <memory>
#include "common.h"


NNInfo_uptr default_info()
{
  MAKE_NNINFO(info);
  info->message = MSG::INIT_ERROR;
  info->result = NNUNKNOWN;
  info->stack = nullptr;
  return info;
}

void append_info(NNInfo_uptr& info)
{
  if(info->stack != nullptr && info->stack->result != NNOK)
    {
      info->message = "";
      info->result = NNERROR;
    }
  else
    {
      info->message = "";
      info->result = NNOK;
    }
}

// Keeps drilling through stack to get the deepest error message
// If stack is shallow, returns the string
// Otherwise, returns a stack of the messages and releases the stack
std::string extract_release_error(NNInfo_uptr& info)
{
  if(info->result == NNOK)
    {
      return "";
    }
  else
    {
      if(info->stack ==  nullptr)
	{
	  return info->message;
	}
      else
	{
	  info->message += "\n";
	  info->message += extract_release_error(info->stack);
	  info->stack.release();
	  info->stack = nullptr;
	  return info->message;
	}
    }
}
