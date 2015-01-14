/* disp.h */
#include <curses.h>

void init_curses(void);
void end_curses(void);
void blue_disp(void);
void red_disp(void);
void disp_tile_row(WINDOW *,int row_data, int pos_x, int pos_y);
