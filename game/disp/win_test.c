#include <curses.h>

void init_color_pair(){
	init_pair(1, COLOR_BLACK, COLOR_RED);
}

// $B%&%#%s%I%&$r=P$9$?$a$N%F%9%H%W%m%0%i%`(B
int main()

{
	WINDOW *win;
	char c;


	/* $B=i4|2=(B */
	initscr();

	init_color_pair();

	start_color();

	/* $B%(%3!<!?%P%C%U%!%j%s%06X;_(B */
	noecho();
	cbreak();

	/* $B%&%#%s%I%&:n@.(B */
	win = newwin(LINES,COLS-1,0,0);
	attrset(1);

	box(win,'|','-');

	/* $B%a%C%;!<%8IA2h(B */
	mvwaddstr(win,1,3,"SAMPLE PROGRAM");
	mvwaddstr(win,3,3,"    CODE :");
	mvwaddstr(win,5,3,"   HITKEY:");
	mvwaddstr(win,7,3,"   END:ESC");
	wrefresh(win);
	while((c = wgetch(win)) != 0x1b){
		char buff[36];

		sprintf(buff,"%02X",c);

		mvwaddstr(win,3,14,buff);
		mvwaddch(win,5,14,c);
		wrefresh(win);
	}

	/* $B8e=hM}(B */
	wclear(win);

	wrefresh(win);
	endwin();
}
