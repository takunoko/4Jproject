# 全体のメインとしてのMakefile

CC = gcc
OPTION = -lncurses

main : main.o game/game.o game/disp/disp.o
	${CC} ${OPTION} -o $@ $^

.o.c :
	${CC} -c $@

clean :
	rm -f *.o main
	rm -f game/*.o
	rm -f game/disp/*.o
	rm -f netfork/*.o
