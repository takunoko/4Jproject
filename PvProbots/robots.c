#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "getchar.h"

/* robot�ط������ */
#define PLAYER 4
#define ROBOT  2
#define SCLAP  1
#define NONE   0

/* �ե�����ɴط� */
/* x:y=2:1���餤������Ū�����Ǹ��䤹�� */
#define MAPXSIZE 20 /* Map��x�����礭�� */
#define MAPYSIZE 10 /* Map��y�����礭�� */

/* Player��Enemy�ο� */
#define ENEMY     5 /* Level���������Ũ�ο� */
#define MAXENEMY 41 /* �ץ쥤�䡼+Ũ�κ���� */

/* �ץ쥤���� */
#define SCORE 0
#define LEVEL 1
#define END 2
#define CLEAR 3
#define MAXINFO 4

/* PC,NPC�˴ؤ���x,y��ɸ */
/* NPC���˲�Ƚ����˲�����Ƥ���вᤷ�����������Ͽ������¤�� */
typedef struct
{
  int x;
  int y;
  int dead;
  int cnt;
} Point;

/* �ץ쥤��˻��Ȥ���flag��score��Ż�᤿��¤�� */
typedef struct
{
  int i;
} Info;

/* map�ν������Ԥ��ؿ� */
void initialise(int map[MAPXSIZE][MAPYSIZE]);

/* PC,NPC�˴ؤ�����ֺ�ɸ���˲�Ƚ��Ȥ��ηв᥿���������������ؿ� */
void refresh(Point list[MAXENEMY]);

/* level�˹�碌��robot�κ���������ꤹ��ؿ� */
int  robot_factory(int lv);

/* robot�κ�����˹�碌�ƥޥåפ�PC,NPC�����֤���ؿ� */
/* Ʊ���˹�¤�Τ�PC,NPC�ΰ��ֺ�ɸ��Ͽ���� */
void spawn(int map[MAPXSIZE][MAPYSIZE],int bot,Point list[MAXENEMY]);

/* �ޥåפȥ�������ɽ������ؿ� */
/* �ޥåפˤ�PC,NPC��Ʊ����ɽ������� */
void print_stats(int map[MAPXSIZE][MAPYSIZE],Info book[MAXINFO]);

/* �ץ쥤�䡼�ΰ�ư�����Ԥ��ؿ� */
/* getChar���Ѥ��ƥꥢ�륿����ι�����ԤäƤ��� */
void player_turn(int map[MAPXSIZE][MAPYSIZE],Point list[MAXENEMY]);

/* robot�ΰ�ư�����Ԥ��ؿ� */
/* Ʊ���˥ץ쥤�䡼��robot���ܿ�Ƚ���ԤäƤ���*/
void robot_turn(int map[MAPXSIZE][MAPYSIZE],Point list[MAXENEMY],int bot,Info book[MAXINFO]);

/* ������Υ��ꥢȽ���Ԥ��ؿ� */
void level_clear(int map[MAPXSIZE][MAPYSIZE],Point list[MAXENEMY],int bot,Info book[MAXINFO]);


int main(void)
{
  srand((unsigned)time(NULL));
  
  int field[MAPXSIZE][MAPYSIZE];
  int robot_max = 0;

  Point list[MAXENEMY];
  Info book[MAXINFO];

  /* level��flag�ν���� */
  /* ENDflag=1�ǥ����ཪλ */
  /* CLEARflag=1��level���ꥢ*/
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
