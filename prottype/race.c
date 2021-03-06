#include <curses.h>
#include <unistd.h>
#include <time.h>

#define dist 1000
#define width 3

int race(int seed){
  int d,ch,py,px;
  int wx,wy;
  int flag = 0;
  srand(seed);
  if(!initscr()) return 1;
  noecho();
  nonl();
  cbreak();
  wtimeout(stdscr,0);
  keypad(stdscr,TRUE);
  leaveok(stdscr,TRUE);
  getmaxyx(stdscr,wy,wx);

  // RETRY:
  curs_set(0);
  clear();
  py = width-1;
  px = 20;
  int i;

  for(i=0;i<4;i++){
    mvprintw(3,10,"A game starts %d seconds later.",3-i);
    sleep(1);
    refresh();
  }

  clear();

  for(d=0;d<dist+px-1;++d){
    usleep(100000 - (d * 100));
    ch = getch();
    if(d % width == 0) move(rand() % width+1 ,0),addch('*');
    /*
      if(d == dist){
      mvaddch(0,0,'G'),
      mvaddch(1,0,'O'),
      mvaddch(2,0,'A'),
      mvaddch(3,0,'L'),
      mvaddch(4,0,'!');
      flag = 1;
      }
    */
    mvinsch(0,0,"=|="[d%width]);
    mvinsch(1,0,' ');
    mvinsch(2,0,' ');
    mvinsch(3,0,' ');
    mvinsch(4,0,"=|="[d%width]);
    mvaddch(py,px+1,'-');

    py += -(ch == KEY_UP && py > 0) + (ch == KEY_DOWN && py < width+1);
    if(py == 0)py = 1;
    else if(py == 4)py = 3;
    move(py,px);
    if(inch() != ' ') {
      mvprintw(7,10,"Game over");
      break;
    }
    addstr("<\b");
    mvprintw(10,10,"Score:%d",d+1);
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
	mvprintw(3,10,"Your Score is %d",d);

  timeout(-1);

  endwin();

	// d $B%9%3%"(B
  return d;
}
