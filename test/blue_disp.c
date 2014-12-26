#include <curses.h>

void blue_disp(void){

  initscr();

  start_color();
  init_pair(2,COLOR_BLUE,COLOR_BLUE);

  clear();
  bkgd(COLOR_PAIR(2));
  curs_set(0);
  getch();
  endwin();             //端末処理の終了
}
