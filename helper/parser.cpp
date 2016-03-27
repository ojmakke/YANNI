/*
 * console_printer.cpp
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
#include <stdlib.h>

#include "parser.h"

Parser::Parser()
{
  p_size      = 0;
  *parameters  = nullptr;
  command     = "";
}

void Parser::parse(char *input_command, size_t command_size)
{
  // Example: text1(text2(text3, text4(text5, text6), text7), text8)
  // text1 has 2 parameters, text2 and text8
  // text2 has 3 parameters: text3, text4, text7
  // ...
  std::string cmd(input_command, command_size);

  //Find the first (, search for all commas until ). Ignore everything
  // inside embedded ()
  size_t firstP = cmd.find('(');
  if(firstP - 1 < 1)
    {
      return; // Error! Don't crash
    }
  command = cmd.substr(0, firstP - 1);
  std::string rest = cmd.substr(firstP, cmd.length());  // rest of string


  int p_opened = 0;   // Number of opened paranthesis
  int p_closed = 0;

  // Sanity check on paranthesis
  for(size_t i = 0; i < rest.length(); i++)
    {
      if(rest.at(i) == '(')
        {
          p_opened++;
        }
      else if(rest.at(i) == ')')
        {
          p_closed++;
        }

      if(p_closed > p_opened)
        {
          return; // Input error
        }
    }

  const int PARSING = 0;
  const int IGNORING = 1;
  int state = PARSING;


  // Search for the comma that ends the paramter, or end of line.
  // Then get parameter
  for(int i = 0; i < rest.length(); i++)
    {
    }
}


Parser::~Parser()
{
  // Traverse the tree, depth first, and delete objects recursively
  for(size_t i = 0; i < p_size; i++)
    {
       clean_tree(parameters[i]);
    }
  // Now all parameters are deleted. Nothing else is allocated.
}

void Parser::clean_tree(Parser *parser)
{
  if(parser->p_size == 0)
    {
      return; //By design, we clean the children, not self, by returning
    }
  for(int i = 0; i < parser->p_size; i++)
    {
      clean_tree(parameters[i]);
      delete parameters[i];
    }
  delete[] parser;  // We go to parent node, clean all childen and repeat...
  return;
}
