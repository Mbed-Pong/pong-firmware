CC = g++ 
PROG = pong
DEPS = src/GameState.h 
CPPFLAGS = -c -Wall -Iinclude
OBJS = main.o GameState.o Sprite.o Network.o 

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)
main.o :
	$(CC) $(CPPFLAGS) -c main.cpp

GameState.o :
	$(CC) $(CPPFLAGS) -c GameState.cpp 

Sprite.o :
	$(CC) $(CPPFLAGS) -c Sprite.cpp 

Network.o :
	$(CC) $(CPPFLAGS) -c Network.cpp 

clean: 
	rm -f core $(PROG) $(OBJS)
