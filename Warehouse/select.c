#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>

int main(void)
{
  MEVENT event;
  int input;

  if(initscr() == NULL){
    fprintf(stderr, "initscr failure\n");
    exit(EXIT_FAILURE);
  }

  cbreak();
  keypad(stdscr, TRUE);

  mousemask(BUTTON1_PRESSED |
	    BUTTON3_PRESSED |
	    REPORT_MOUSE_POSITION,
	    NULL);
  refresh();

  while((input = mvwgetch(stdscr, 0, 0)) != 'q'){
    if(input == KEY_MOUSE){
      mvprintw(2, 5, "mouse event");
      if(getmouse(&event) != OK){
	mvprintw(3, 5, "getmouse failure");
	continue;
      }
      mvprintw(3, 5, "x = %d, y = %d, z = %d", event.x, event.y, event.z);
      if(event.bstate == BUTTON1_PRESSED){
	mvprintw(event.y, event.x, "*");
      }
      else if(event.bstate == BUTTON3_PRESSED){
	mvprintw(event.y, event.x, " ");
      }
      refresh();
    }
    else{
      mvprintw(2, 5, "not mouse event %c", input);
    }
  }

  endwin();
  exit(EXIT_SUCCESS);
}
