CC = gcc
CURSES_OPTION = -lncurses
USE_FILES = disp.o
all : main win_test test_win_2

main : main.c ${USE_FILES}
	${CC} ${CURSES_OPTION} -o $@ $^

win_test : win_test.c
	${CC} ${CURSES_OPTION} -o $@ $^

test_win_2 : test_win_2.c
	${CC} ${CURSES_OPTION} -o $@ $^

.c.o:
	${CC} -c $^
