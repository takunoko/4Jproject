#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct node{
  char user_id[2];           /*�桼����ID*/
  char user_rank[2];         /*���*/
  char user_time[6];         /*������*/
};

void assign(struct node *result , char game_res[]);

int main(void)
{
  struct node result;
  char ranking_list[4];

	/* ��������Ƥ���ǡ����η���
	 * �桼����ID ��� ����
	 *	3 1 2.5
	 * �ߤ����ʴ���
	 */
  char game_res_A[] = "A 2 4.8";
  char game_res_B[] = "B 4 7.2";
  char game_res_C[] = "C 1 3.0";
  char game_res_D[] = "D 3 6.1";


  /*��ʪ�ϿͿ��ο�����forʸ���*/
  assign(&result , game_res_A);

  return 0;

}

void assign(struct node *result , char game_res[])
{
  int i,j,k;
  int count = 0;
  char cut_elem[10];    /*�ڤ�Ф���ʸ����*/


  i=j=k=0;

  /*3�Ĥ����Ǥ�ʬ�䡦����*/
  if(count == 0){
    for(i=0;game_res[i]!=' ';i++){}
    strncpy(result->user_id , game_res , i);
    result->user_id[1] = '\0';
    printf("%s\n", result->user_id);
    count++;
  }
  if(count == 1){
    for(j=i+1;game_res[j]!=' ';j++){}
    strncpy(result->user_rank , game_res+i+1 , j);
    result->user_rank[1] = '\0';
    printf("%s\n" , result->user_rank);
    count++;
  }
  if(count == 2){
    for(k=j+1;game_res[k]!=' ';k++){}
    strncpy(result->user_time , game_res+j+1 , k);
    result->user_time[3] = '\0';
    printf("%s\n" , result->user_time);
    count++;
  }
}
