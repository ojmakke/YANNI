/*
 * console_printer.h
 *
 *  Created on : Mar 26, 2016
 *      Author : Omar Makke (O jMakke)
 *      ojQuote: "How do we change the world? One line of code at a time"
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

#ifndef CONSOLE_PRINTER_H
#define CONSOLE_PRINTER_H

#define BUFFERSIZE 80
#define INPUTHEIGHT 4
// Row in input window
#define YINPUT 1
// Input offset. Account for |> which is 2 chars
#define XOFFSET 2

#include <ncurses.h>

// Singleton
// Not thread safe.
class ConsolePrinter
{
public:
  WINDOW *w_input;
  WINDOW *w_network;
  WINDOW *w_feedback;

  static ConsolePrinter& instance();
  void interact();
  void input_write(char c);
  void feedback_write(char c);
  void network_write(char c);

  ~ConsolePrinter();

private:
  char commands[BUFFERSIZE]; //allow commands of 80
  size_t ii_input;    // index to input buffer;
  size_t ii_feedback; // index to feedback window buffer;
  size_t ii_network;  // index to network buffer;
  ConsolePrinter();

  ConsolePrinter(ConsolePrinter const&);        // Don't Implement
  void operator=(ConsolePrinter const&);        // Don't copy
  // Credit goes to ncurses developers with these. They provided examples
  void init_screen();
  void reset_input_cursor();  // Move curser to input window after writing
  void clear_command();
  void switch_console_state(unsigned int *state);
  void rescale();
  void draw_network();
  void draw_feedback();
  void draw_input();
  void print_feedback1();// TODO: better naming. This is info1
  WINDOW *create_newwin(int height, int width, int starty, int startx);
  void destroy_win(WINDOW *local_win);
  void destroy_screen();

};

#endif // CONSOLE_PRINTER_H
