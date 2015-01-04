CC = gcc
CURSES_OPTION = -lncurses
USE_FILES = disp.o

main : main.c ${USE_FILES}
	${CC} ${CURSES_OPTION} -o $@ $^

.c.o:
	${CC} -c $^
