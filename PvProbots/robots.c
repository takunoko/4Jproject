#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "getchar.h"

/* robot関係の定義 */
#define PLAYER 4
#define ROBOT  2
#define SCLAP  1
#define NONE   0

/* フィールド関係 */
/* x:y=2:1ぐらいが画面的に綺麗で見やすい */
#define MAPXSIZE 20 /* Mapのx軸の大きさ */
#define MAPYSIZE 10 /* Mapのy軸の大きさ */

/* PlayerとEnemyの数 */
#define ENEMY     5 /* Level毎に増える敵の数 */
#define MAXENEMY 41 /* プレイヤー+敵の最大数 */

/* プレイ情報 */
#define SCORE 0
#define LEVEL 1
#define END 2
#define CLEAR 3
#define MAXINFO 4

/* PC,NPCに関するx,y座標 */
/* NPCの破壊判定と破壊されてから経過したターン数を記録した構造体 */
typedef struct
{
  int x;
  int y;
  int dead;
  int cnt;
} Point;

/* プレイ中に参照するflagとscoreを纏めた構造体 */
typedef struct
{
  int i;
} Info;

/* mapの初期化を行う関数 */
void initialise(int map[MAPXSIZE][MAPYSIZE]);

/* PC,NPCに関する位置座標と破壊判定とその経過ターン数を初期化する関数 */
void refresh(Point list[MAXENEMY]);

/* levelに合わせてrobotの最大数を設定する関数 */
int  robot_factory(int lv);

/* robotの最大数に合わせてマップにPC,NPCを配置する関数 */
/* 同時に構造体にPC,NPCの位置座標を記録する */
void spawn(int map[MAPXSIZE][MAPYSIZE],int bot,Point list[MAXENEMY]);

/* マップとスコアを表示する関数 */
/* マップにはPC,NPCも同時に表示される */
void print_stats(int map[MAPXSIZE][MAPYSIZE],Info book[MAXINFO]);

/* プレイヤーの移動制御を行う関数 */
/* getCharを用いてリアルタイムの更新を行っている */
void player_turn(int map[MAPXSIZE][MAPYSIZE],Point list[MAXENEMY]);

/* robotの移動制御を行う関数 */
/* 同時にプレイヤーとrobotの接触判定を行っている*/
void robot_turn(int map[MAPXSIZE][MAPYSIZE],Point list[MAXENEMY],int bot,Info book[MAXINFO]);

/* ゲームのクリア判定を行う関数 */
void level_clear(int map[MAPXSIZE][MAPYSIZE],Point list[MAXENEMY],int bot,Info book[MAXINFO]);


int main(void)
{
  srand((unsigned)time(NULL));
  
  int field[MAPXSIZE][MAPYSIZE];
  int robot_max = 0;

  Point list[MAXENEMY];
  Info book[MAXINFO];

  /* levelとflagの初期化 */
  /* ENDflag=1でゲーム終了 */
  /* CLEARflag=1でlevelクリア*/
  book[LEVEL].i = 1;
  book[END].i = 0;
  book[CLEAR].i = 0;
  
  initialise(field);
  refresh(list);
  robot_max = robot_factory(book[LEVEL].i);
  spawn(field,robot_max,list);

  while(1){
    print_stats(field,book);
    player_turn(field,list);

    robot_turn(field,list,robot_max,book);
    if(book[END].i == 1)break;

    level_clear(field,list,robot_max,book);
    if(book[CLEAR].i == 1){
      book[LEVEL].i++;
      initialise(field);
      refresh(list);
      robot_max = robot_factory(book[LEVEL].i);
      if(robot_max > MAXENEMY)	robot_max = MAXENEMY;
      spawn(field,robot_max,list);
      book[CLEAR].i = 0;
    }
  }
  printf("Game over\n");
  return 0;
}

void initialise(int map[MAPXSIZE][MAPYSIZE])
{
  int x,y;
  
  for(y=0;y<MAPYSIZE;y++)
  {
    for(x=0;x<MAPXSIZE;x++)
    {
      map[x][y] = NONE;
    }
  }
}

void refresh(Point list[MAXENEMY])
{
  int i;

  for(i=0;i<MAXENEMY;i++)
  {
    list[i].x = NONE;
    list[i].y = NONE;
    list[i].dead = NONE;
    list[i].cnt = NONE;
  }
}

int robot_factory(int lv)
{
  int rt = 0;
  
  rt = ENEMY * lv;
  
  return rt;
}

 
void spawn(int map[MAPXSIZE][MAPYSIZE],int bot,Point list[MAXENEMY])
{
  int x = 0,y = 0;
  int i;
  
  for(i=0;i<=bot;i++)
  {
    x = rand() % (MAPXSIZE - 2);
    y = rand() % (MAPYSIZE - 2);
    x++;
    y++;
    
    while(map[x][y] == ROBOT)
    {
      x++;
      if(x % (MAPXSIZE-1) == 0){
	x = 1;
	y++;
      }
      if(y % (MAPYSIZE-1) == 0){
	y = 1;
      }
    }
    if(i == 0){
      map[x][y] = PLAYER;
      list[i].x = x;
      list[i].y = y;
    }
    else{
      map[x][y] = ROBOT;
      list[i].x = x;
      list[i].y = y;
    }
  }
}

void print_stats(int map[MAPXSIZE][MAPYSIZE],Info book[MAXINFO])
{
  int x=0,y=0;
  
  for(y=0;y<MAPYSIZE;y++)
  {
    for(x=0;x<MAPXSIZE;x++)
    {
      int f1 = x % (MAPXSIZE-1) == 0;
      int f2 = y % (MAPYSIZE-1) == 0;
      //if(x==0&&y==0||x==(MAPXSIZE-1)&&y==0||x==0&&y==(MAPYSIZE-1)||x==(MAPXSIZE-1)&&y==(MAPYSIZE-1)) printf("+");
      if(f1 && f2) printf("+");
      else if(f1) printf("|");
      else if(f2) printf("-");
      else{
	if(map[x][y] == PLAYER)     printf("@");
	else if(map[x][y] == ROBOT) printf("+");
	else if(map[x][y] == SCLAP) printf("*");
	else if(map[x][y] == NONE)  printf(" ");
      }
    }
    printf("\n");
  }
  printf("Level:%d  Score:%d\n",book[LEVEL].i,book[SCORE].i);
}

void player_turn(int map[MAPXSIZE][MAPYSIZE],Point list[MAXENEMY])
{
  char pm = 0;
  int dx,dy;
  
 start:
  
  do{
    pm = getChar();
  }while('0' > pm || pm > '9');
  
  if(pm == '0')
  {
    dx = (rand() % (MAPXSIZE - 2)) + 1;
    dy = (rand() % (MAPYSIZE - 2)) + 1;
  }
  else if(pm == '1')
  {
    dx = -1;
    dy = 1;
  }
  else if(pm == '2')
  {
    dx = 0;
    dy = 1;
  }
  else if(pm == '3')
  {
    dx = 1;
    dy = 1;
  }
  else if(pm == '4')
  {
    dx = -1;
    dy = 0;
  }
  else if(pm == '5')
  {
    dx = 0;
    dy = 0;
  }
  else if(pm == '6')
  {
    dx = 1;
    dy = 0;
  }
  else if(pm == '7')
  {
    dx = -1;
    dy = -1;
  }
  else if(pm == '8')
  {
    dx = 0;
    dy = -1;
  }
  else if(pm == '9')
  {
    dx = 1;
    dy = -1;
  }
  
  int f1 = (list[0].x + dx) % (MAPXSIZE-1) == 0;
  int f2 = (list[0].y + dy) % (MAPYSIZE-1) == 0;
  
  if(f1 || f2) goto start;
  else if(map[list[0].x+dx][list[0].y+dy] == SCLAP) goto start;
  else
  {   
    map[list[0].x][list[0].y] = NONE;
    if(pm == '0'){
      list[0].x = dx;
      list[0].y = dy;
    }
    else{
      list[0].x += dx;
      list[0].y += dy;
    }
    map[list[0].x][list[0].y] = PLAYER;
  }
  
}


void robot_turn(int map[MAPXSIZE][MAPYSIZE],Point list[MAXENEMY],int bot,Info book[MAXINFO])
{
  int i;
  int dx = 0,dy = 0;

  for(i=1;i<=bot;i++){

    dx = (list[0].x > list[i].x) - (list[0].x < list[i].x);
    dy = (list[0].y > list[i].y) - (list[0].y < list[i].y);

    //printf("[%d] = %d, %d\n", i, dx, dy);
    
      if(map[list[i].x][list[i].y] == SCLAP){
      dx = 0;
      dy = 0;
      }
    
    if(map[list[i].x+dx][list[i].y+dy] == PLAYER)
    {
      book[END].i = 1;
      break;
    }
    else if(map[list[i].x+dx][list[i].y+dy] == NONE)
    {
      book[END].i = 0;
      map[list[i].x][list[i].y] = NONE;
      list[i].x += dx;
      list[i].y += dy;
      map[list[i].x][list[i].y] = ROBOT;
    }
    else if(map[list[i].x+dx][list[i].y+dy] == ROBOT || map[list[i].x+dx][list[i].y+dy] == SCLAP)
    {
      book[END].i = 0;
      map[list[i].x][list[i].y] = NONE;
      list[i].x += dx;
      list[i].y += dy;
      map[list[i].x][list[i].y] = SCLAP;
      list[i].dead = 1;
      list[i].cnt++;
      if(list[i].dead == 1 && list[i].cnt == 1){
	book[SCORE].i++;
      }
    }
  }
  
}

void level_clear(int map[MAPXSIZE][MAPYSIZE],Point list[MAXENEMY],int bot,Info book[MAXINFO])
{
  int i;
  int sclap = 0;

  for(i=1;i<=bot;i++){
    if(map[list[i].x][list[i].y] == SCLAP)
    {
      sclap++;
    }
  }

  if(sclap == bot)
  {
    book[CLEAR].i = 1;
    book[SCORE].i = book[SCORE].i + (book[LEVEL].i * 10);
  }
}
