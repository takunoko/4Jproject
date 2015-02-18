// �Ȥꤢ������ʸ�������ɤϤ��Τޤޤǥ��ʥ��㥹 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHAR_SIZE 30

static int x=0;                    /*ɽ����X��ɸ*/
static int y=0;                    /*ɽ����Y��ɸ*/
static int user;                   /*�桼������*/
static int counter=0;              /*XY��ɸ���������󥿡�*/

typedef struct{
	char user_id[CHAR_SIZE];           /*�桼����ID*/
	char user_rank[CHAR_SIZE];
	char user_score[CHAR_SIZE];
}NODE;

int perce(NODE *results, char *str);
void assign(NODE *result , char game_res[]);          /*��¤�Τ˳�Ǽ*/
void disp_result(NODE *result, int, int);
void disp(NODE result);                               /*ɽ��*/

int main_dummy(void)
{
	NODE result[20]; /* ����ä�¿��˳��� */

	int size;

	char game_res[] = "APPLE 1 23.0\nB 2 2.4\nCAPTAIN 3 3.5\nDONKY 8 6.8\n4 7 6.0\nF 6 5.5\nGO 4 4.2\nH 10 8.9\nI 9 7.0\nJfwefep9u 5 4.3";

	/* ��¤�Τ˥ǡ������Ǽ */
	size = perce( result, game_res);

	// for(size--; size>=0; size--){
	// 	printf("%s,%s,%s,\n", result[size].user_id, result[size].user_rank, result[size].user_score);
	// }

	disp_result( result, size, 4);

	return 0;

}

// ����ͤ˥ǡ����ο�����
int perce(NODE *result, char *str){
	int size;

	char parce_char[] = "\n";
	char *tmp;

	size = 0;
	tmp = strtok( str, parce_char);
	while( tmp != NULL ){
		assign( &result[size], tmp);  // iwaʸ����ѡ����ؿ�
		tmp = strtok( NULL, parce_char);
		size++;
	}

	return size-1;
}

/*�ǡ�����Ǽ�ؿ�*/
void assign(NODE *result , char game_res[])
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
		strncpy(result->user_rank , game_res+i+1 , j-i-1);
		result->user_rank[j-i] = '\0';
		// printf("%s\n",result->user_rank);
		count++;
	}

	/*������*/
	if(count == 2){
		for(k=j+1;game_res[k]!='\0';k++){}
		strncpy(result->user_score , game_res+j+1 , k-j);
		result->user_score[k-j] = '\0';
		count++;
	}
}

// ��̤�ɽ��
void disp_result(NODE *result, int player_size, int my_id){
	int i;
	int pos_x, pos_y;
	char char_my_id[10];

	sprintf(char_my_id,"%d",my_id);

	for(i=0; i<player_size; i++){
		if(strcmp(char_my_id,result[i].user_id) == 0){
			printf("You :%5s[rank]:%5s[pt]\n", result[i].user_rank, result[i].user_score);
		}else{
			printf("Name:%5s[rank]:%5s[pt]\n", result[i].user_rank, result[i].user_score);
		}
		// mvprintw(pos_y, pos_x, result[i].user_id);
		// mvprintw(pos_y, pos_x+10, result[i].user_id);
		// mvprintw(pos_y, pos_x+20, result[i].user_id);
	}
}

/*ɽ��������ؿ�*/
/* �����ʤ��� curses�����Ѥ���Τǡ�����ȻȤ��ʤ��Ǥ�
 * ���ʤ꤭�줤�Ǥ��줷���Τ����ɡ�����
 */

/*
void disp(NODE result){
	int i;


	// �ǽ��ɽ���򤹤�Ȥ��˲��̤���������
	if(counter == 0){
		printf("\033[2J");         // ���̤򥯥ꥢ
		printf("\033[%d;%dH",y,x); // ��ɸ����
		printf("\x1b[31m");        // ʸ��������
		printf("------------------------------------------ R E S U L T ------------------------------------------\n");
		printf("\x1b[39m");
	}


	// 5��2��ɽ��
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

	// 1�̡��ν�Ƿ�̤�ɽ������Ȳ��ꤷ��3�̤ޤǤ�ʸ�������ѹ�����(��̤ȥ�����Τ�)

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
	printf("%s\n" , result.user_score);
	printf("\x1b[39m");

	counter++;

}
*/
