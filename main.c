#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// DEGUBを宣言すると、ifdef DEBUGのところも実行されるようになる
#define DEBUG
// 手札の最大枚数
#define HAND_CARD_SIZE 25

typedef struct {
	int card[HAND_CARD_SIZE]; // プレイヤーの持っているカード Maxで25枚ぐらいしか持たないでしょ
	int card_num;	// カードの枚数を保持
	int play_flg; // このユーザーがゲームに勝利とかしていないかの判定
}PLAYER;

void init_program();
int set_player();
void init_game( int, PLAYER*);
void change_int( int*, int*);
void game();

int main(void){
	init_program();	// なんか、乱数の初期化とかするときに使う
	game();

	return 0;
}

void init_program(){
	// 乱数の初期化
	srand((unsigned)time(NULL));
}

// 人数の決定
int set_player(){
	int player_num = 0;
	do{
		printf("何人でプレイしますか？(3~6)");
		scanf("%d",&player_num);
	}while(player_num < 3 || player_num > 6);

	return player_num;
}

// ゲームの初期化
void init_game(int player_size, PLAYER players[]){
	int card[54];
	int i;

	// カードの初期化
	for(i=0; i<54; i++){
		card[i] = i;
	}

	// カードのシャッフル
	for(i=0; i<54; i++){
		change_int( &card[i], &card[rand()%54]);
	}

#ifdef DEBUG
	// とりあえずシャッフルしたカードを表示
	puts("shuffle");
	for(i=0; i<54; i++){
		printf("%d = %d\n", i, card[i]);
	}
#endif

	int j;
	for(j=0; j<player_size; j++){
		for(i=0; i<HAND_CARD_SIZE; i++){
			players[j].card[i] = -1;
		}
		players[j].card_num = 0;
	}
	// 各プレイヤーにカードを代入
	for(i=0; i<54; i++){
		players[i%player_size].card[i/player_size] = card[i];
		players[i%player_size].card_num++; // カードの枚数をカウント
	}

#ifdef DEBUG
	// 配られたカードの確認
	for(j=0; j<player_size; j++){
		printf("P:%d  ", j);
		for(i=0; i<players[j].card_num; i++){
			printf(" %2d,", players[j].card[i]);
			// 表示内容
			// P:プレイヤー C(n番目, カードの種類)
		}
		putchar('\n');
	}
#endif
}

// ゲーム開始
void game(){
	int player_size;
	PLAYER players[6];

	player_size = set_player();

	// ゲームループ
	while(1){
		init_game( player_size, players);

		// このへんにゲームの更新処理を書いていく
		//
		break;
	}
}

// 交換
void change_int( int *x, int *y){
	int tmp;
	tmp = *x;
	*x = *y;
	*y = tmp;
}


