#include <curses.h>
#include <unistd.h>
#include <time.h>

#define dist 1000
#define width 3

int main(void){
  int d,ch,py,px;
  int wx,wy;
  int flag = 0;
  srand(time(NULL));
  if(!initscr()) return 1;
  noecho();
  nonl();
  cbreak();
  wtimeout(stdscr,0);
  keypad(stdscr,TRUE);
  leaveok(stdscr,TRUE);
  getmaxyx(stdscr,wy,wx);

  // RETRY:
  /* 速度の調節を行う */
  curs_set(0);
  clear();
  py = 2;
  px = 20;
  for(d=0;d<dist+px-1;++d){
<<<<<<< HEAD
    if(d < 100)     usleep(100000);
    else if(d < 200)usleep(90000);
    else if(d < 250)usleep(80000);
    else if(d < 300)usleep(70000);
    else if(d < 400)usleep(60000);
=======
		usleep(100000 - (d * 100));
		// usleep(100000);
		// usleep(60000);
>>>>>>> 12590086a9118a01d515cfb8be11f52f06675e07
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
  timeout(-1);
  getch();

  clear();
  printw("Your Score is %d",d);

  timeout(-1);
  getch();

  endwin();
  return 0;
}
