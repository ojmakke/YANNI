#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

#include "common.h"

extern WINDOW *w_input;
extern WINDOW *w_network;
extern WINDOW *w_feedback;

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);

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

