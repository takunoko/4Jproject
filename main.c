#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "game/game.h"

// プログラム自体の初期化
void init_program(void){
	srand((unsigned)time(NULL));
}


int main(void){
	init_program();

	game_loop();

	return 0;
}
