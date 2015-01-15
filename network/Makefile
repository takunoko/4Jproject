CC = gcc
OPTION = -Wall -v

CREATE_FILES = game_server game_client network_main

all : ${CREATE_FILES}

network_main : network_main.o network.o
	${CC} ${OPTION} -o $@ $^

game_server : game_server.o network.o
	${CC} ${OPTION} -o $@ $^

game_client : game_client.o network.o
	${CC} ${OPTION} -o $@ $^

clean :
	rm *.o
	rm ${CREATE_FILES}
