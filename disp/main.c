#include <stdlib.h>

#include "disp.h"

int main(void){
	init_curses();

  blue_disp();
  getch();             //ボタン入力待ち

	red_disp();
  getch();             //ボタン入力待ち

	end_curses();

  return 0;
}
