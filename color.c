#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <curses.h>

#define CARD 53
#define MARK 4
#define A 1
#define J 11 
#define Q 12
#define K 13

#define RED 1
#define BLACK 2

void color(int player_num,PLAYER players[]){

  int l=0,i=0,j=0;
  int card;

  initscr(); //���դ������

  /* ����¸�ߤ��Ƥʤ���н�λ */
  if(has_colors() == FALSE){
    endwin();
    exit(EXIT_FAILURE);
  }

  /* ��������ߤ����ʤ��*/
  /* sttrset(COLOR_PAIR(BLACK or RED))�ǸƤӽФ��� */
  start_color();
  init_pair(RED,COLOR_RED,COLOR_WHITE);
  init_pair(BLACK,COLOR_BLACK,COLOR_WHITE);

  /* ����� */
  /* players[].card[]�����ͤ����ĥ�ä�4��;���Ф��ƿ��Ĥ��Ƥ� */
  for(i=0;j<player_num;i++){

    if(players[j].card[i] == NULL){
      i = 0;
      j++;
    }

    card = players[j].card[i];
    if(card>=52) l=5;
    else l = card % 4;

    if(l==0){
      sttrset(COLOR_PAIR(BLACK));
      printw("[s-%d]",card);
    }
    else if(l==1){
      attrset(COLOR_PAIR(RED));
      printw("[d-%d]",card);
    }
    else if(l==2){
      attrset(COLOR_PAIR(BLACK));
      printw("[c-%d]",card);
    }
    else if(l==3){
      attrset(COLOR_PAIR(RED));
      printw("[h-%d]",card);
    }
    else if(l==5){
      attrset(COLOR_PAIR(BLACK));
      printw("[P]");
    }
  }

}
