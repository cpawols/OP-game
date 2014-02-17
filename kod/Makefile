CPPFLAGS = -Wall -pedantic  -std=c++11

all : test

objects:  plansza.o przedmioty.o stworzenie.o 

test: test.cpp objects
	g++  $(CPPFLAGS) test.cpp *.o  -o test

clean :
	rm -f bst *.o
