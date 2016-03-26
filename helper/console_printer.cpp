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
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

#include "../common.h"
#include "console_printer.h"

#define CONTROL 0
#define INPUT 1

const char *feedback1[] = {
                            "F1 to quit anytime",
                            "F2 to rescale window",
                            "i to insert commands (INSERT mode)",
                            "ESC to quit INSERT mode",
                            "s to save network parameters",
                            "v for basic network parameters",
                            "h for more help",
                          };

ConsolePrinter::ConsolePrinter()
{
  ii_feedback = 0;
  ii_network = 0;
  ii_input = 0;
  init_screen();
}

ConsolePrinter& ConsolePrinter::instance()
{
  static ConsolePrinter instance;
  return instance;
}

void ConsolePrinter::print_feedback1()
{
  const int ROWOFFSET = 1;
  const int COL       = 2;
  for(size_t i = 0; i < ARRAY_SIZE(feedback1); i++)
    {
      mvwprintw(w_feedback, i+ROWOFFSET, COL, feedback1[i]);
    }
  wrefresh(w_feedback);
}

void ConsolePrinter::draw_input()
{
  const int COLOFFSET = 3;
  const int IOFFSET = 1;
  wattron(w_input, COLOR_PAIR(2));
  werase(w_input);
  box(w_input, 0, 0);
  mvwprintw(w_input, 0, COLOFFSET, "User Input");
  mvwprintw(w_input, YINPUT, IOFFSET, ">");
  keypad(w_input, true);
  noecho();
  wrefresh(w_input);
  clear_command();
  ii_input = 0;
}

void ConsolePrinter::draw_feedback()
{
  const int COLOFFSET = 3;
  wattron(w_feedback, COLOR_PAIR(1));
  werase(w_feedback);
  box(w_feedback, 0, 0);
  mvwprintw(w_feedback, 0, COLOFFSET, "Feedback");
  print_feedback1();
  wrefresh(w_feedback);
}

void ConsolePrinter::draw_network()
{
  const int COLOFFSET = 3;
  wattron(w_network, COLOR_PAIR(3));
  werase(w_network);
  box(w_network, 0, 0);
  mvwprintw(w_network, 0, COLOFFSET, "Network Info");
  wrefresh(w_network);
}

void ConsolePrinter::init_screen()
{
  int row, col;
  initscr();
  clear();
  cbreak();
  noecho();
  refresh();
  getmaxyx(stdscr,row,col);
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_CYAN, COLOR_BLACK);

  w_input = create_newwin(4, col, row-4, 0);
  w_feedback = create_newwin(row-4, col/2-1,0,0);
  w_network = create_newwin(row-4, col/2+1, 0,col/2-1);
  draw_feedback();
  draw_network();
  draw_input();

}

void ConsolePrinter::destroy_screen()
{
  destroy_win(w_input);
  destroy_win(w_network);
  destroy_win(w_feedback);
  endwin();
}

WINDOW* ConsolePrinter::create_newwin(int height, int width, int starty, int startx)
{
  WINDOW *local_win;
  local_win = newwin(height, width, starty, startx);
  box(local_win, 0 , 0);
  wrefresh(local_win);
  return local_win;
}

void ConsolePrinter::destroy_win(WINDOW *local_win)
{
  wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
  wrefresh(local_win);
  delwin(local_win);
}

void ConsolePrinter::rescale()
{
  destroy_screen();
  clear_command();
  init_screen();
}

void ConsolePrinter::reset_input_cursor()
{
  // move the cursor to input location
  mvwprintw(w_input, YINPUT,ii_input+XOFFSET, "");
  wrefresh(w_input);
}

// TODO consider what happens when screen is less than 80
// What happens if we attempt to write beyond visible limit?
void ConsolePrinter::input_write(char c)
{
  int row, col;
  getmaxyx(stdscr,row,col);
  // backspace
  if(c == KEY_BACKSPACE  || c == KEY_DC || c == 07 || c == 8)
    {
      if(ii_input == 0)
        {
          return; //Do nothing
        }
      commands[ii_input--] = 0; // Remove buffer char
      // To erase on screen, write space to clear pixels and then "" to clear space.
      // TODO: Find better method
      mvwprintw(w_input, YINPUT, ii_input + XOFFSET, " ");
      wrefresh(w_input);
      mvwprintw(w_input, YINPUT, ii_input + XOFFSET, "");
      wrefresh(w_input);
      return;
    }
   if(c == 10 || c == 13)
    {
      commands[ii_input] = 0; // Terminating null.
      ii_input = 0;
      // parse_command
      draw_input();
      reset_input_cursor();
    }
  // Escape
  else if(c == 27)
    {
     return;  // do nothing
    }
  // Attempts to protect against writing beyond visible screen.
  else if(ii_input >= (size_t) col - XOFFSET-2)
    {
      return;
    }
  // Ignore invalid chars
  else if( c < 33 || c > 126)
    {
      return;
    }
  // Cap input and replace last char in input
  else if(ii_input >= BUFFERSIZE - 2)
    {
      mvwprintw(w_input, YINPUT, ii_input + XOFFSET - 1, "%c", c);
      reset_input_cursor();
      commands[BUFFERSIZE - 2] = c;
      wrefresh(w_input);
      return;
    }
  mvwprintw(w_input, YINPUT, ii_input + XOFFSET, "%c", c);
  commands[ii_input++] = c;
  return;
}

void ConsolePrinter::clear_command()
{
  memset(commands, 0, BUFFERSIZE);
}

void ConsolePrinter::interact()
{
  int ch;
  unsigned int state = CONTROL;
  bool completed = false;
  while(!completed)
    {
      ch = wgetch(w_input);
      switch(ch)
        {
        // Never allowed in input. This quits
        case KEY_F(1):
          {
            return;
            break;
          }
        // Reset everything
        case KEY_F(2):
          {
            rescale();
            state = CONTROL;
          }
          break;
         // In control mode, do nothing. Otherwise, insert \0
        case 10:
        case 13:
          {
            if(state == CONTROL)
              {
                continue;
              }
            // Parse input first
            input_write(ch);
          }
          break;
        // Escape resets everything
        case 27:
          {
            if(state == CONTROL)
              {
                continue;
              }
            switch_console_state(&state);
          }
          break;
        case 'i':
          {
            if(state == CONTROL)
              {
                switch_console_state(&state);
                break;
              }
            input_write(ch);
          }
          break;
        default:
          if(state == CONTROL)
            {
              continue;
            }
          input_write(ch);
          break;
        }
    }
  return;
}


void ConsolePrinter::switch_console_state(unsigned int *state)
{
  switch(*state)
    {
    case CONTROL:
      {
        *state = INPUT;
      }
      break;
    case INPUT:
      {
        *state = CONTROL;
      }
    break;
    }
}

ConsolePrinter::~ConsolePrinter()
{
  destroy_screen();
}

