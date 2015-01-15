#define PLAYER_MAX_SIZE 20 // プレイヤー数の最大数
#define TILE_SIZE 50 // 消化すべきパネルの数
#define PENALTY_TIME 100000 // [us] パネルをミスった時のペナルティー時間

#include <stdio.h>
#include <unistd.h> // sleepを使う
#include <stdlib.h> // 乱数を使う
#include <sys/time.h> // マイクロ秒計測関数 gettimeofday()

/* #include <time.h>
 * 時間の計測 clock_t clock() を使う
 * clock()を使うと、一応分解能が秒単位
 */

#include "disp/disp.h"

// スリープ(秒)
void my_sleep(int t){
	usleep(t*1000000);
}

// ゲームの初期化関数
// 戻り値として、プレイヤー数を返す
int init_game(){
	int player_num;
	int i;

	// とりあえず、ローカルで実行できるように
	// printf("Player: \n"); scanf("%d",&player_num);
	player_num = 1;

	return player_num;
}

int* create_tile(int seed, int *tail_data){
	int i;

	srand(seed); // シード値を同じにすることで、同じ乱数を発生させる
	for(i=0; i < TILE_SIZE; i++){
		tail_data[i] = rand()%4+1;
		printf("%d ",tail_data[i]);
	}
	putchar('\n');

	return tail_data;
}

void game_loop(){
	int player_size;
	int tile_data[TILE_SIZE]; // ゲームのマップデータ

	char dummy;

	struct timeval start, end; // 時間計測用

	player_size = init_game();  // ゲームの初期化

	// これは、書くゲームループごとにやる
	int seed;
	seed = 3;
	create_tile( seed, tile_data);			// タイルデータの初期化


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
