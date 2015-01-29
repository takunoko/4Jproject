CC = gcc
OPTION_CURSES = -lncurses

race : main.c race.o
	${CC} ${OPTION_CURSES} -o $@ $^

.o.c :
	${CC} -c $^

clean :
	rm *.o
	rm race
