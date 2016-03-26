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

#define BUFFERSIZE 80
#define CONTROL 0
#define INPUT 1
#define INPUT_LOCATION 1


NNHelper<double> nnhelper;

extern void run_tests();
extern void destroy_screen();
extern void init_screen();
extern void draw_input();
extern void draw_feedback1();
extern void draw_network();

void switch_state(unsigned *state);

WINDOW *w_input;
WINDOW *w_network;
WINDOW *w_feedback;


void clear_command(char *command)
{
  memset(command, 0, BUFFERSIZE);
}

size_t insert_char(char *command, char c, size_t index)
{
  if( c < 32 || c > 126)
    {
      return index; // Ignore non-ascii characters
    }
  if(index >= BUFFERSIZE - 2)
    {
      command[BUFFERSIZE - 2] = c;
      return (BUFFERSIZE - 2);
    }
  command[index++] = c;
  return index;
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
  size_t ii = 0; // Buffer index
  char commands[80];
  clear_command(commands);
  while(1)
    {
      ch = wgetch(w_input);
      switch(ch)
        {
        // Never allowed in input. This quits
        case KEY_F(1):
          {
            return 0;
            break;
          }
        // Reset everything
        case KEY_F(2):
          {
            destroy_screen();
            init_screen();
            ii = 0;
            clear_command(commands);
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
            commands[ii] = 0; // Terminating null.
                             // ii points to last index by design
            ii = 0;
            // parse_command
            clear_command(commands);
            draw_input();

          }
          break;
        // Escape resets everything
        case 27:
          {
            if(state == CONTROL)
              {
                continue;
              }
            clear_command(commands);
            ii = 0;
            switch_state(&state);
          }
          break;
        case 'i':
          {
            if(state == CONTROL)
              {
                ii = 0;
                clear_command(commands);
                switch_state(&state);
                break;
              }
            mvwprintw(w_input, 1, ii+2, "%c", ch);
            ii = insert_char(commands, ch, ii);
          }
          break;
        default:
          if(state == CONTROL)
            {
              continue;
            }
          mvwprintw(w_input, 1, ii+2, "%c", ch);
          ii = insert_char(commands, ch, ii);
          break;
        }
    }

  destroy_screen();
  return 0;
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
