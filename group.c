/* ��ʬ���ץ���� */
#include	<stdio.h>
#include	<stdlib.h>

/* ������ */
#define		N_STUDENTS		(39)

/* ��륰�롼�פο� */
#define		N_GROUPS		(13)

main(void)
{
	int		group[N_STUDENTS];
	int		i;
	int		r;
	int		t;
	int		seed;

	/* �֤Ǥ������ǡפ����� */
	printf("�������Ϥ��Ƥ�������: ");
	scanf("%d",&seed);
	srandom(seed);

	/* 0 1 2 3 ... N 0 1 2 3 ... N 0 1 2 3 ...	*/
	/* �����ֹ���������� group �˳�Ǽ����		*/
	for (i = 0;i < N_STUDENTS;i++){
		group[i] = i % N_GROUPS;
	}

	/* �ֹ��Ǥ������¤��ؤ��� */
	for (i = N_STUDENTS - 1;i > 0;i--){
		r = random() % i;
		t = group[r];
		group[r] = group[i];
		group[i] = t;
	}

	/* �Ǥ������ä����롼�פ�ɽ������ */
	printf("�ֹ�\t���롼��\n");
	for (i = 0;i < N_STUDENTS;i++){
		printf("%2d\t%2d\n",i + 1, group[i] + 1);
	}
}
