#define CHAR_SIZE 30

typedef struct{
	char user_id[CHAR_SIZE];           /*ユーザーID*/
	char user_rank[CHAR_SIZE];
	char user_score[CHAR_SIZE];
}NODE;

int perce(NODE *results, char *str);
void assign(NODE *result, char game_res[]);          /*構造体に格納*/
void disp_result(NODE *result, int, int);
