#include <stdio.h>
#include <string.h>

int main(void){
	int id, rank, score;
	char *tmp;

	char str[] = "42 2 3.5\n32 4 6.2\n54 11 6.4";
	char str2[] = "\n";

	tmp = strtok( str, str2);
	while( tmp != NULL ){
		printf("%s\n", tmp);
		sscanf(tmp,"%d %d %d", &id, &rank, &score);
		printf("%d,%d,%d\n", id, rank, score);
		tmp = strtok( NULL, str2);
	}

	return 0;
}


