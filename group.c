/* 斑分けプログラム */
#include	<stdio.h>
#include	<stdlib.h>

/* 学生数 */
#define		N_STUDENTS		(39)

/* 作るグループの数 */
#define		N_GROUPS		(13)

main(void)
{
	int		group[N_STUDENTS];
	int		i;
	int		r;
	int		t;
	int		seed;

	/* 「でたらめの素」を設定 */
	printf("数を入力してください: ");
	scanf("%d",&seed);
	srandom(seed);

	/* 0 1 2 3 ... N 0 1 2 3 ... N 0 1 2 3 ...	*/
	/* の斑番号を生成して group に格納する		*/
	for (i = 0;i < N_STUDENTS;i++){
		group[i] = i % N_GROUPS;
	}

	/* 番号をでたらめに並べ替える */
	for (i = N_STUDENTS - 1;i > 0;i--){
		r = random() % i;
		t = group[r];
		group[r] = group[i];
		group[i] = t;
	}

	/* できあがったグループを表示する */
	printf("番号\tグループ\n");
	for (i = 0;i < N_STUDENTS;i++){
		printf("%2d\t%2d\n",i + 1, group[i] + 1);
	}
}
