#include <curses.h>

void red_disp(void)
{
  /* 色付けに関する初期化 */
  initscr(); 
  
  /* 色のdefine定義 */
  start_color();
  init_pair(1,COLOR_BLACK,COLOR_RED);
  
  clear();             //スクリーンをクリアし、リフレッシュ
  bkgd(COLOR_PAIR(1)); //スクリーンカラー変更
  curs_set(0);         //カーソル非表示(1)で表示
  getch();             //ボタン入力待ち

}
