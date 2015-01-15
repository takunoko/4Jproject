all : network game_server

network : network.o
	gcc -o $@ $^

game_server : game_server.o network.o
	gcc -o game_server game_server.o network.o

.o.c :
	cc -c $@
