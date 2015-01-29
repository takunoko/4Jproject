#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct node{
  char id;            /*ユーザーID*/
  char rank;          /*ランク*/
  char time;       /*タイム*/
};

void get_res(char str[]);                       /*文字列受け取り*/
void subst(struct node *result , char str[]);   /*構造体に代入*/
void list(struct node result , char lists[10][3]);  /*リスト作成*/

int main(void)
{
  struct node result;
  char str[10];
  char str2[10][3];
  int i,j;
  
  get_res(str);
  subst(&result,str);
  list(result,str2);
 
  printf("ID: %c RANK: %c TIME: %c\n" , result.id , result.rank , result.time);
  
  for(j=0;j<10;j++){
    for(i=0;i<3;i++){
      printf("%2d ",str2[j][i]);
      printf("\n");
    }
  }

  return 0;
}


void get_res(char str[])
{
  char res[10] = "42 2 3.5";

  strcpy(str,res);

}

void subst(struct node *result , char str[])
{
  char id;
  char rank;
  char time;

  printf("%s\n",str);

  sscanf(str, "%c %c %c", &id, &rank, &time);

  result->id = id;
  result->rank = rank;
  result->time = time;

}

void list(struct node result , char lists[10][3])
{
  int i,j;

  for(j=0;j<10;j++){
    for(i=0;i<3;i++){
      
      if(i == 0){
	lists[j][i] = result.id;
      }else if(i == 1){
	lists[j][i] = result.rank;
      }else if(i == 2){
	lists[j][i] = result.time;
      }
      
    }
  }

}
  
