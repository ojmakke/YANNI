/*
 * workspace.cpp
 *
 *  Created on : Mar 26, 2016
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

#include "workspace.h"
#include "console_printer.h"

extern void run_tests();

Workspace::Workspace()
{

}

void Workspace::execute(Parser &parser)
{
  size_t layer_size;

  if(parser.command.compare("demo") == 0)
    {
      ConsolePrinter::instance().feedback_rewrite(
            "Starting Demo...                   ");
      run_tests();
    }
  else
    {
      std::string result = "Unrecognized command: ";
      result.append(parser.command).append(". Try demo");
      ConsolePrinter::instance().feedback_rewrite(result);
    }
}
