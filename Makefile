main: main.o common.o diffusion.o transport.o
	g++ main.o common.o diffusion.o transport.o -o main
main.o: main.cpp common.h diffusion.h transport.h
	g++ -c main.cpp
common.o: common.h common.cpp
	g++ -c common.cpp
diffusion.o: diffusion.cpp diffusion.h common.h
	g++ -c diffusion.cpp
transport.o: transport.cpp transport.h
	g++ -c transport.cpp

clean:
	rm -f *.o main *.eps *.txt *.pdf
cleanM:
	rm -f main
