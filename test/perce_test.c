#include <stdio.h>

int main(void){
	int id;
	int rank;
	double time;
	char *tmp;

	char str[] = "42 2 3.5";

	sscanf(str, "%d %d %lf", &id, &rank, &time);

	printf("id: %d rank: %d time: %f\n", id, rank, time);

	return 0;
}


