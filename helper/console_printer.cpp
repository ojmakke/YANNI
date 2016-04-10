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
#include "parser.h"
#include "console_printer.h"
#include "workspace.h"

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
  vi_feedback = 0;
  vi_network = 0;
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

  const int COL = 2;
  for(size_t i = 0; i < ARRAY_SIZE(feedback1); i++)
    {
      mvwprintw(w_feedback,  vi_feedback++, COL, feedback1[i]);
    }

  vi_feedback++;
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
  vi_feedback = 2;
  print_feedback1();
}

void ConsolePrinter::draw_network()
{
  const int COLOFFSET = 3;
  wattron(w_network, COLOR_PAIR(3));
  werase(w_network);
  box(w_network, 0, 0);
  mvwprintw(w_network, 0, COLOFFSET, "Network Info");
  wrefresh(w_network);
  vi_network = 1;
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
void ConsolePrinter::input_write(int c)
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

      std::string command = std::string(commands);
      Parser parser;
      parser.parse(command, 1);
      Workspace::instance().execute(parser);
      draw_input();
      reset_input_cursor();
      return;
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

bool ConsolePrinter::interact()
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
            return false;
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
            // This will get teh command too
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
  return false;
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

void ConsolePrinter::feedback_rewrite(std::string feedback)
{
  if(vi_feedback > (size_t) LINES - INPUTHEIGHT - 1)
    {
      vi_feedback = 10;
    }
  mvwprintw(w_feedback, vi_feedback, 2, "%s    ", feedback.c_str());
  wrefresh(w_feedback);
}

void ConsolePrinter::feedback_write(std::string feedback)
{
  feedback_rewrite(feedback);
  vi_feedback++;
}

void
ConsolePrinter::network_write_nets(std::vector<FullHidden<double> *>& nets)
{
  for(size_t ii = 0; ii < nets.size(); ii++)
    {
      mvwprintw(w_network, 5+ii, 2, "%d FullHidden", nets.at(ii)->self_id);
    }
  wrefresh(w_network);
}

void ConsolePrinter::network_write_active(FullHidden<double> *net)
{
  mvwprintw(w_network, 2, 2, "%d is Active", net->self_id);
  wrefresh(w_network);
}

ConsolePrinter::~ConsolePrinter()
{
  destroy_screen();
}
