#include <curses.h>

// curses関連の処理を行う際に最初に実行
void init_curses(){
	// cursesの利用開始　
  initscr();

	// 利用する色の初期化
	start_color();
  init_pair(2,COLOR_BLUE,COLOR_BLUE);
  init_pair(1,COLOR_BLACK,COLOR_RED);

  curs_set(0);         //カーソル非表示(1)で表示
}

// curses関連の処理を終わる際に必ず実行
// プログラムの最後で実行しないと描画がおかしくなることが多々
void end_curses(){
  endwin();             //端末処理の終了
}

void blue_disp(void){
  clear();
  bkgd(COLOR_PAIR(2));
	refresh();
}

void red_disp(void)
{
  clear();             //スクリーンをクリアし、リフレッシュ
  bkgd(COLOR_PAIR(1)); //スクリーンカラー変更
	refresh();
}
