CC = g++ 
PROG = pong
DEPS = src/GameState.h 
CPPFLAGS = -c -Wall -Iinclude
OBJS = main.o GameState.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)
main.o :
	$(CC) $(CPPFLAGS) -c main.cpp

GameState.o :
	$(CC) $(CPPFLAGS) -c GameState.cpp 


clean: 
	rm -f core $(PROG) $(OBJS)
