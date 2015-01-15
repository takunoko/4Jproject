#include <curses.h>
#include <unistd.h>
#include <time.h>

#define dist 200
#define width 3

int main(void){
  int d,ch,py,px;
  int flag = 0;
  srand(time(NULL));
  if(!initscr()) return 1;
  noecho();
  nonl();
  cbreak();
  wtimeout(stdscr,0);
  keypad(stdscr,TRUE);
  leaveok(stdscr,TRUE);

  // RETRY:
  curs_set(0);
  clear();
  py = 2;
  px = 20;
  for(d=0;d<dist+px-1;++d){
    usleep(100000);
    ch = getch();
    if(d % width == 0) move(rand() % width+1 ,0),addch('*');
    if(d == dist){
      mvaddch(0,0,'G'),
	mvaddch(1,0,'O'),
	mvaddch(2,0,'A'),
	mvaddch(3,0,'L'),
	mvaddch(4,0,'!');
      flag = 1;
    }
    mvinsch(0,0,"=|="[d%width]);
    mvinsch(1,0,' ');
    mvinsch(2,0,' ');
    mvinsch(3,0,' ');
    mvinsch(4,0,"=|="[d%width]);
    mvaddch(py,px+1,'-');
    
    py += -(ch == KEY_UP && py > 0) + (ch == KEY_DOWN && py < width+1);
    move(py,px);
    if(inch() != ' ') break;
    addstr("<\b");
    refresh();
  }
  /*
  curs_set(1);
  mvaddstr(5,0,"retry or quit [r/q] ?");
  refresh();
  do{
    ch = getch();
    if(ch == 'r') goto RETRY;
  }while(ch != 'q');
  */
  clear();
  if(flag)mvaddstr(4,34,"CLEAR");
  else    mvaddstr(4,34,"GAME OVER");

  timeout(-1);
  getch();

  endwin();
  return 0;
}
