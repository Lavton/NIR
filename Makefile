main: main.o common.o diffusion.o
	g++ main.o common.o diffusion.o -o main
main.o: main.cpp common.h diffusion.h
	g++ -c main.cpp
common.o: common.h common.cpp
	g++ -c common.cpp
diffusion.o: diffusion.cpp diffusion.h common.h
	g++ -c diffusion.cpp