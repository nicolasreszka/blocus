blocus : menu.o grid.o draw.o play.o main.o
	gcc -o blocus menu.o grid.o draw.o play.o main.o -lgraph
 
menu.o : menu.c menu.h
	gcc -c menu.c

grid.o : grid.c grid.h 
	gcc -c grid.c

draw.o : draw.c draw.h
	gcc -c draw.c

play.o : play.c play.h
	gcc -c play.c
 
main.o : main.c menu.h grid.h draw.h play.h
	gcc -c main.c