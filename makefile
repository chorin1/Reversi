a.out: Board.o main.o
	g++ Board.o main.o

main.o: main.cpp Board.h
	g++ -c main.cpp

Board.o: Board.cpp Board.h
	g++ -c Board.h Board.cpp
