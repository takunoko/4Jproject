#include <stdlib.h>

#include "disp.h"

int main(void){
	init_curses();

  // blue_disp();
  // getch();             //ボタン入力待ち

	// red_disp();

	// disp_tile_row( 3, 5, 5);
	// disp_tile_row( 3, 5, 7);
  getch();             //ボタン入力待ち

	end_curses();

  return 0;
}
