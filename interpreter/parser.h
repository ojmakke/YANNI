/*
 * parser.h
 *
 *  Created on : Mar 26, 2016
 *      Author : Omar Makke (O jMakke)
 *      ojQuote: "Math is simply a numeric implementation of Logic."
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

#ifndef PARSER_H
#define PARSER_H

#include <string>

class Parser
{
public:
  Parser();
  std::string command;
  Parser **parameters; // Parameters of the command. This is like a tree.
  size_t p_size; // Arguments: Size of parameters
  void parse(std::string input_command, bool is_root);
  ~Parser();

private:


  void clean_tree(Parser *parser);
};


// for the interpreter
namespace FUNCS
{
  const std::string TANH = "tanh";
  const std::string LOGISTIC = "logistic";
  const std::string RECTIFY = "rectify";
  const std::string STEP = "step";
  const std::string FIXEDINPUT = "fixedinput";
  const std::string POWERN = "powern";
}


#endif // PARSER_H
