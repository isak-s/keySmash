#include <ncurses.h>
#include <unistd.h>

#define DELAY 35000

int main(int argc, char *argv[]) {
  int x = 0,
      y = 0;

  int max_x = 0,
      max_y = 0;

  int next_x = 0;

  int direction = 1;

  initscr();
  noecho();
  curs_set(TRUE);

  getmaxyx(stdscr, max_y, max_x);

  x = max_x / 2;
  y = max_y / 2;

  mvprintw(y, x, "HERE WE HAVE some text");
  refresh();
  getch();

  endwin();

  return 0;
}