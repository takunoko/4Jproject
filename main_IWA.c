#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// DEGUBを宣言すると、ifdef DEBUGのところも実行されるようになる
#define DEBUG
// 手札の最大枚数
#define HAND_CARD_SIZE 25

typedef struct {
	int card[HAND_CARD_SIZE]; // プレイヤーの持っているカード Maxで25枚ぐらいしか持たないでしょ
	int play_flg; // このユーザーがゲームに勝利とかしていないかの判定
}PLAYER;

void init_program();                //乱数とかの初期化
int set_player();                   //遊ぶ人数の設定(3〜6人)
void init_game(int, PLAYER*);       //ゲームの初期化(カードの初期化、シャッフル等)
void change_int( int*, int*);       //カードの交換？
void game();                        //ゲームの処理
void draw(PLAYER*)                  //毎ターンの開始にカードを引く動作
int menu(int play_num);             //メニューの表示 戻り値は選択した行動

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
	printf("シャッフルしたカードを表示します\n");
	for(i=0; i<54; i++){
	  printf("%d = %d\n", i, card[i]);
	}

#endif
	
	int j;
	for(j=0; j<player_size; j++){
	  for(i=0; i<HAND_CARD_SIZE; i++){
	    players[j].card[i] = -1;
	  }
	}
	// 各プレイヤーにカードを代入
	for(i=0; i<54; i++){
	  players[i%player_size].card[i/player_size] = card[i];
	}
	
#ifdef DEBUG
	// 配られたカードの確認
	printf("各プレイヤーの手札を表示します\n");
	for(j=0; j<player_size; j++){
	  for(i=0; i<25; i++){
	    printf("P:%d C(%d, %d)\n", j, i, players[j].card[i]);
	    // 表示内容
	    // P:プレイヤー C(n番目, カードの種類)
	  }
	}
#endif
}

// ゲーム開始
void game(){
  int player_size;      //プレイヤーの人数
  int i;
  int menu_num;         //メニュー＋選択関数で選択した値を受け取る
  PLAYER players[6];
  
  player_size = set_player();
  
  // ゲームループ
  while(1){
    init_game( player_size, players);
    
    // このへんにゲームの更新処理を書いていく
    
    //一連の動作を人数分だけfor文を用いて回す
    for(i = 0; i < player_size; i++){
      //ターンの開始はカードを引くよ
      draw(players);
      //引き終わったらメニューを表示する
      menu_num = menu(i);
 

    }
    
    
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

// プレイヤーメニュー
int menu(int play_num){
  int play_choose;
  printf("PLAYER%dのターン\n" , play_num);
  printf("=============== PLAYER'S MENU ================\n");
  printf("[0] : 手札の表示\n");
  printf("[1] : カードを捨てる\n");
  printf("[2] : 相手の手札の枚数を確認\n");
  printf("[3] : パス\n");
  printf("==============================================\n");
  printf("何をしますか？ : ");
  scanf("%d",&play_choose);
  }
  

int main(void){
	init_program();	// なんか、乱数の初期化とかするときに使う
	game();

	return 0;
}

// ドロー作業
void draw(PLAYER*){}
