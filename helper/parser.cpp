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
#include <cassert>

#include "parser.h"

Parser::Parser()
{
  p_size      = 0;
  *parameters  = nullptr;
  command     = "";
}

// Note: The input to this must be clear of white space
void Parser::parse(std::string input_command)
{
  // Example: text1(text2(text3, text4(text5, text6), text7), text8)
  // text1 has 2 parameters, text2 and text8
  // text2 has 3 parameters: text3, text4, text7
  // ...
  std::string cmd(input_command);
  cmd.append(" "); // Makes life much easier in parsing when looping
  int p_opened = 0;   // Number of opened paranthesis

  // Search for the breadth of parameters to allocate memory while
  // checking syntax.
  // A paramter is detected by counting # of valid commas (p_opened=1)
  // between paranthesis
  size_t breadth_width = 0;
  for(size_t ii = 0; ii < cmd.length() - 1; ii++) // last is ' ' ii+1 is afe
    {
      // Verify comma is between parenthesis
      if(cmd.at(ii) == ',' && p_opened == 0)
        {
          return;     // Illegal use of commas. Separating what?
        }
      // Insure we have ), or )). Nothing like )text or )(
      // After all ) we are good
      else if(  cmd.at(ii) == ')' && (ii < cmd.length() - 1)
             && cmd.at(ii+1) != ',' && cmd.at(ii+1) != ')')
        {
          return;
        }
      // Insure we have no ,( or ,)
      // After all commas we are good
       else if(  cmd.at(ii) == ','
             && (cmd.at(ii+1) == '(' || cmd.at(ii+1) == ')'))
         {
            return;
         }
      // Insure have no () or (,
      // After all ( we are good.
      else if(  cmd.at(ii) == '('
            && (cmd.at(ii+1) == ')' || cmd.at(ii+1) == ','))
        {
           return;
        }
      // At this point, after all special symbols we are good.
      // Also, the location of all symbols is good (comma inside parenthesis)
      // Verify that first and last symbols are good outside loop
      // By induction,everything is good if paranthesis balance correctly
      else if(cmd.at(ii) == '(')
        {
          p_opened++;
          continue;
        }
      else if(cmd.at(ii) == ')')
        {
          p_opened--;
          if(p_opened < 0)
            {
              return; // Imbalanced
            }
          continue;
        }
      else if(cmd.at(ii) == ',' && p_opened == 1)
        {
          breadth_width++;
        }
    }

  if(p_opened > 0)
    {
      return; // Imbalanced parameters
    }

  cmd.pop_back(); // Get rid of alst ' ' that we inserted.

  // Make sure first and last of cmd are valid
  // This also verifies last end. Why?
  // Paranethsis are checked for being balanced :)
  // If last is not a ), then it is text.
  // Hence we either have 1 parameter, or
  // text1,text2 which cannot happen, or
  // text1(text)text2 which cannot happen: no , after ), or
  // text1(text),text2 which cannot happen: p_open = 0
  // or imbalanced ()
  if(cmd.at(0) == '(')
    {
      return; // Invalid ends
    }

  // Create the parameter tree recursively
  if(breadth_width > 0)
    {
     *parameters = new Parser[breadth_width]();
    }

  //Find the first (, search for all commas until ). Ignore everything
  // inside embedded ()
  size_t firstP = cmd.find('(');

  // We have only text, no ()
  if(firstP > cmd.length())
    {
      command = cmd;
      return; // we are done, no parameters for this parameter
    }
  else
    {
      command = cmd.substr(0, firstP - 1);
    }

  std::string rest = cmd.substr(firstP, cmd.length());  // rest of string

  // Search for the comma that ends the parameter, or end of line.
  // Then get parameter. First & last () will be ignored
  // We also ran previous algorithms to determine # parameters in this string.
  p_opened = 0; // Redundant, but for clarity
  size_t breadth_index = 0;
  size_t param_begin = 1; // beginning of parameter. Skip first (
  for(size_t ii = 1; ii < rest.length() - 1; ii++)
    {
      if(rest.at(ii) == '(')
        {
          p_opened++;
          continue;
        }
      // This must be valid
      else if(rest.at(ii) == ')')
        {
          p_opened--;
          continue;
        }
      // now to the conditions which indicate end of parameter
      // 1: a valid , such as text1(text2 COMMA text3 COMMA ..)
      // 2: end of string
      else if(  (rest.at(ii) == ',' && p_opened == 0)
              ||(ii == rest.length() - 1))
        {
          std::string sub_cmd = rest.substr(param_begin, ii);
          param_begin = ii+1; // Skip this comma
          Parser *parser = new Parser();
          parser->parse(sub_cmd);   // Recursive. Creates depth tree
          assert(breadth_index < breadth_width); // Just to make sure
          parameters[breadth_index++] = parser;
        }
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
  for(size_t i = 0; i < parser->p_size; i++)
    {
      if(parameters[i] != nullptr)  // in case parsing got error.
        {
          clean_tree(parameters[i]);
          delete parameters[i];
        }
    }
  delete[] parser;  // We go to parent node, clean all childen and repeat...
  return;
}
