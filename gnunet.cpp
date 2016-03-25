/*
 * gnunet.cpp
 *
 *  Created on: Mar 17, 2016
 *      Author: Omar Makke (O jMakke)
 */
#include <ncurses.h>
#include <panel.h>
#include <string.h>
#include <menu.h>
#include <stdlib.h>
#include <form.h>

#include "activation/tanh.hpp"
#include "activation/logistic.hpp"
#include "activation/step.hpp"
#include "activation/rectify.hpp"
#include "helper/nnhelper.hpp"

#define CONTROL 0
#define INPUT 1
#define INPUT_LOCATION 1

NNHelper<double> nnhelper;

extern void run_tests();

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);
void switch_state(unsigned *state);

WINDOW *w_input;
WINDOW *w_network;
WINDOW *w_feedback;

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
char *feedback1[] =
                {
                 "F1 to quit anytime",
                 "F2 to rescale window",
                 "i to insert command",
                 "s to save network parameters",
                 "v for basic network parameters",
                 "h for more help",
                };

void print_feedback1()
{
  for(size_t i = 0; i < ARRAY_SIZE(feedback1); i++)
    {
      mvwprintw(w_feedback, i+1, 2, feedback1[i]);
    }
  wrefresh(w_feedback);
}

void draw_input()
{
  wattron(w_input, COLOR_PAIR(2));
  werase(w_input);
  box(w_input, 0, 0);
  mvwprintw(w_input, 0, 3, "User Input");
  mvwprintw(w_input, 1, 1, ">");
  keypad(w_input, true);
  noecho();
  wrefresh(w_input);
}

void draw_feedback()
{
  wattron(w_feedback, COLOR_PAIR(1));
  werase(w_feedback);
  box(w_feedback, 0, 0);
  mvwprintw(w_feedback, 0, 3, "Feedback");
  print_feedback1();
  wrefresh(w_feedback);
}

void draw_network()
{
  wattron(w_network, COLOR_PAIR(3));
  werase(w_network);
  box(w_network, 0, 0);
  mvwprintw(w_network, 0, 3, "Network Info");
  wrefresh(w_network);
}

void init_screen()
{
  char f[] = "Feedback\0";
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

void destroy_screen()
{
  destroy_win(w_input);
  destroy_win(w_network);
  destroy_win(w_feedback);
  endwin();
}

int main(int argc, char* argv[])
{
  int ch;
  init_screen();

  wrefresh(w_input);
  // Apply state machine.
  // control: keys are for control, not inputting command
  // input: RELEVANT keys are used for inputting.

  unsigned int state = CONTROL;
  while(1)
    {
      ch = wgetch(w_input);
      switch(ch)
        {
        // Never allowed in input. This quits
        case KEY_F(1):
          return 0;
          break;
        // Never allowed in input.
        case KEY_F(2):
          {
            destroy_screen();
            init_screen();
            state = CONTROL;
          }
          break;
         // Allow only in input
        case 10:
        case 13:
          {
            if(state == CONTROL)
              {
                continue;
              }
  //          switch_state(&state);
            draw_input();
            echo();

          }
          break;
        // Escape
        case 27:
          {
            if(state == CONTROL)
              {
                continue;
              }
            switch_state(&state);
          }
          break;
        case 'i':
          if(state == CONTROL)
            {
              switch_state(&state);
            }
          break;
        default:
          if(state == CONTROL)
            {
              continue;
            }
          break;
        }
    }

  destroy_screen();
  return 0;
}

WINDOW *create_newwin(int height, int width, int starty, int startx)
{
  WINDOW *local_win;
  local_win = newwin(height, width, starty, startx);
  box(local_win, 0 , 0);
  wrefresh(local_win);
  return local_win;
}

void destroy_win(WINDOW *local_win)
{
  wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
  wrefresh(local_win);
  delwin(local_win);
}

void switch_state(unsigned int *state)
{
  switch(*state)
    {
    case CONTROL:
      {
        *state = INPUT;
        echo();
      }
      break;
    case INPUT:
      {
        *state = CONTROL;
        draw_input();
      }
    break;
    }
}
