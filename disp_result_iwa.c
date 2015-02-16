#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int x=0;                    /*ɽ����X��ɸ*/
static int y=0;                    /*ɽ����Y��ɸ*/
static int user;                   /*�桼������*/
static int counter=0;              /*XY��ɸ���������󥿡�*/

struct node{
  char user_id[10];           /*�桼����ID*/
  char user_rank[10];         /*���*/
  char user_time[10];         /*������*/
};

void assign(struct node *result , char game_res[]);          /*��¤�Τ˳�Ǽ*/
void disp(struct node result);                               /*ɽ��*/

int main(void)
{
  struct node result1;
  struct node result2;
  struct node result3;
  struct node result4;
  struct node result5;
  struct node result6;
  struct node result7;
  struct node result8;
  struct node result9;
  struct node result10;

  /*�̿�¦���������Ƥ�����
    �桼�����οͿ�����̥ǡ�����ʸ����*/

	/* ��������Ƥ���ǡ����η���
	 * �桼����ID ��� ����
	 *	A 1 2.5
	 * �ߤ����ʴ���
	 */
  
  /*̾������̡����֤Ϥ��줾��10ʸ������Ǥ���Ȳ���*/
  /*�Ȥꤢ�����ץ��������Ѱ�*/
  char game_res_A[] = "APPLE 1 2.0";
  char game_res_B[] = "B 2 2.4";
  char game_res_C[] = "CAPTAIN 3 3.5";
  char game_res_D[] = "DONKY 8 6.8";
  char game_res_E[] = "EEEEEEEE 7 6.0";
  char game_res_F[] = "F 6 5.5";
  char game_res_G[] = "GO 4 4.2";
  char game_res_H[] = "H 10 8.9";
  char game_res_I[] = "I 9 7.0";
  char game_res_J[] = "Jfwefep9u 5 4.3";
  int member = 10;
  int i;
  
  /*ɽ���ؿ��ǻȤ��ΤǿͿ��򥰥��Х��ѿ��˳�Ǽ���Ƥ���*/
  user = member;
  
  /*��¤�Τ˥ǡ������Ǽ*/
  for(i=0;i<user;i++){
    
    switch(i){
    case 0: assign(&result1 , game_res_A);
            break;
    case 1: assign(&result2 , game_res_B);
            break;
    case 2: assign(&result3 , game_res_C);
            break;
    case 3: assign(&result4 , game_res_D);
            break;
    case 4: assign(&result5 , game_res_E);
            break;
    case 5: assign(&result6 , game_res_F);
            break;
    case 6: assign(&result7 , game_res_G); 
            break;
    case 7: assign(&result8 , game_res_H);
            break;
    case 8: assign(&result9 , game_res_I);
            break;
    case 9: assign(&result10 , game_res_J);
            break;

    }
  }

  /*ɽ��������*/
  for(i=0;i<user;i++){
    
    switch(i){
    case 0: disp(result1);
      break;
    case 1: disp(result2);
      break;
    case 2: disp(result3);
      break;
    case 3: disp(result4);
      break;
    case 4: disp(result5);
      break;
    case 5: disp(result6);
      break;
    case 6: disp(result7);
      break;
    case 7: disp(result8);
      break;
    case 8: disp(result9);
      break;
    case 9: disp(result10);
      break;

    }
  }
 

  return 0;

}

/*�ǡ�����Ǽ�ؿ�*/
void assign(struct node *result , char game_res[])
{
  int i,j,k;
  int count = 0;


  i=j=k=0;

  /*3�Ĥ����Ǥ�ʬ�䡦����*/

  /*̾��*/
  if(count == 0){
    for(i=0;game_res[i]!=' ';i++){}
    strncpy(result->user_id , game_res+0 , i);
    result->user_id[i] = '\0';
    count++;
  }
  
  /*���*/
  if(count == 1){
    for(j=i+1;game_res[j]!=' ';j++){}
    strncpy(result->user_rank , game_res+i+1 , j-i);
    result->user_rank[j-i] = '\0';
    printf("%s\n",result->user_rank);
    count++;
  }
  
  /*������*/
  if(count == 2){
    for(k=j+1;game_res[k]!='\0';k++){}
    strncpy(result->user_time , game_res+j+1 , k-j);
    result->user_time[k-j] = '\0';
    count++;
  }

}


/*ɽ��������ؿ�*/
void disp(struct node result){
  int i;

  
  /*�ǽ��ɽ���򤹤�Ȥ��˲��̤���������*/
  if(counter == 0){
    printf("\033[2J");         /*���̤򥯥ꥢ*/
    printf("\033[%d;%dH",y,x); /*��ɸ����*/
    printf("\x1b[31m");        /*ʸ��������*/
    printf("------------------------------------------ R E S U L T ------------------------------------------\n");
  printf("\x1b[39m");
  }
  

  /*5��2��ɽ��*/
  switch(counter){
  case 0: x=0; y=3; break;
  case 1: x=20; y=3; break;
  case 2: x=40; y=3; break;
  case 3: x=60; y=3; break;
  case 4: x=80; y=3; break;
  case 5: x=0; y=9; break;
  case 6: x=20; y=9; break;
  case 7: x=40; y=9; break;
  case 8: x=60; y=9; break;
  case 9: x=80; y=9; break;
  }
  
  /*1�̡��ν�Ƿ�̤�ɽ������Ȳ��ꤷ��3�̤ޤǤ�ʸ�������ѹ�����(��̤ȥ�����Τ�)*/

  printf("\033[%d;%dH",y,x);
  printf("[ID]");
  printf("%s\n" , result.user_id);
  y++;
  printf("\033[%d;%dH",y,x);
  printf("\x1b[36m");
  printf("[RANK]");
  printf("\x1b[39m");
  if(counter == 0){
    printf("\x1b[31m");
  }else if(counter == 1){
    printf("\x1b[34m");
  }else if(counter == 2){
    printf("\x1b[32m");
  }
  printf("%s\n" , result.user_rank);
  y++;
  printf("\x1b[39m");

  printf("\033[%d;%dH",y,x);
  printf("\x1b[35m");
  printf("[TIME]");
  printf("\x1b[39m");
 if(counter == 0){
    printf("\x1b[31m");
  }else if(counter == 1){
    printf("\x1b[34m");
  }else if(counter == 2){
    printf("\x1b[32m");
  }
  printf("%s\n" , result.user_time);
  printf("\x1b[39m");


  counter++;

}
