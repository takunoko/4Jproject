#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// DEGUBを宣言すると、ifdef DEBUGのところも実行されるようになる
#define DEBUG
// 手札の最大枚数
#define HAND_CARD_SIZE 25

#define NEW_GAME_YES 1
#define NEW_GAME_NO 2

// 各プレイヤーの状態を保持する
typedef struct {
	int id;
	int card[HAND_CARD_SIZE]; // プレイヤーの持っているカード Maxで25枚ぐらいしか持たないでしょ
	int card_num;	// カードの枚数を保持
	int play_flg; // このユーザーがゲームに勝利とかしていないかの判定
}PLAYER;

void init_program();
int set_player();
void init_game( int, PLAYER*);

void game();
int ask_new_game();
void change_int( int*, int*);

void player_do(int, PLAYER*, int);
void select_card(int do_player_num, PLAYER* players, int player_size);
int chk_select_card( PLAYER, int);

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
// このへんで、ネットワークで人数をうまく決定したい
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
		players[j].id = j;
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
	int new_game;
	PLAYER players[6];

	player_size = set_player();

	// ゲームループ
	do{
		int turn_cnt;
		// ゲームの初期化
		init_game( player_size, players);

		// ひとり1行動
		while(1){
			player_do( turn_cnt % player_size, players, player_size);
			turn_cnt++;
		}
		new_game = ask_new_game();
	}while(new_game == NEW_GAME_YES);
}

// 新しいゲームを始めるかの質問
int ask_new_game(){
	char input;
	int ret;
	puts("新しいゲームを始めますか?");
	printf("[ Yes:y, No:n] ");
	scanf(" %c", &input);

	switch(input){
		case 'y':
		case 'Y':
			ret = NEW_GAME_YES;
			break;
		default :
			ret = NEW_GAME_NO;
			break;
	}

	return ret;
}

// player_do( 自分のプレイヤー番号, 全員の手札構造体, 全体のプレイヤー数)
void player_do(int do_player_num, PLAYER* players, int player_size){
	select_card( do_player_num, players, player_size);
}

// むっちゃ適当に手札表示関数を作ってみた
void select_card(int do_player_num, PLAYER* players, int player_size){
	int i,j;
	int choice_card;

	// とりあえず、全員分適当に表示
	do{
		for (i = (do_player_num+1)%player_size; i != do_player_num%player_size; i = (i+1)%player_size) {
			printf("Player : %d\n", i);
			for (j = 0; j < players[i].card_num; j++) {
				printf(" %2d",players[i].card[j]);
			}
			putchar('\n');
		}
		scanf("%d", &choice_card);
		// この辺で"選択できません"とか、コメント出すべきな気がする
	}while(chk_select_card( players[do_player_num%player_size], choice_card));
}

// 可:0 不可:1
int chk_select_card(PLAYER my_card, int choice_card){
	// 手札と選択したカードから出せるか判断
	// テストとして、とりあえず1を表示しておく
	return 0;
}

// 交換
void change_int( int *x, int *y){
	int tmp;
	tmp = *x;
	*x = *y;
	*y = tmp;
}
