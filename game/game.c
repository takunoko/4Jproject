#define PLAYER_MAX_SIZE 20

#include <stdio.h>
#include <unistd.h> // sleepを使う
#include <sys/time.h> // マイクロ秒計測関数 gettimeofday()

/* #include <time.h>
 * 時間の計測 clock_t clock() を使う
 * clock()を使うと、一応分解能が秒単位
 */

#include "disp/disp.h"

// スリープ(秒)
void my_sleep(int t){
	sleep(t);
}

// ゲームの初期化関数
// 戻り値として、プレイヤー数を返す
int init_game(int *player_time){
	int player_num;
	int i;

	for(i=0; i<PLAYER_MAX_SIZE; i++){
		player_time[i] = 0;
	}

	// とりあえず、ローカルで実行できるように
	// printf("Player: \n"); scanf("%d",&player_num);
	player_num = 1;

	return player_num;
}

void game_loop(){
	int players_time[PLAYER_MAX_SIZE];
	int player_size;

	char dummy;

//	clock_t start, end;
	struct timeval start, end;

	player_size = init_game(players_time);


	init_curses(); // cursesを使うための初期化

	red_disp();
	my_sleep(3);
	blue_disp();
	gettimeofday(&start, NULL);
  getch();             //ボタン入力待ち
	gettimeofday(&end, NULL);
	end_curses();

	if (end.tv_usec < start.tv_usec) {
		printf("%d.%d[us]\n", (int)(end.tv_sec - start.tv_sec - 1), (int)(1000000 + end.tv_usec - start.tv_usec));
	}
	else {
		printf("%d.%d[us]\n", (int)(end.tv_sec - start.tv_sec), (int)(end.tv_usec - start.tv_usec));
	}

}
