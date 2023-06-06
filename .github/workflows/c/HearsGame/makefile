# makefile sample

TARGET= Main.out
CC= gcc
CFLAGS= -ansi -g -pedantic
OBJS= vector.o Deck.o Round.o Player.o Game.o  UI.o main.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	
vector.o: vector.c vector.h
	$(CC) $(CFLAGS) -c vector.c
	
Game.o: Game.c Game.h Deck.h vector.h Round.h Player.h Card.h ADTDefs.h
	$(CC) $(CFLAGS) -c Game.c
	
Deck.o: Deck.c Deck.h vector.h Card.h ADTDefs.h
	$(CC) $(CFLAGS) -c Deck.c

Player.o: Player.c Player.h vector.h Card.h ADTDefs.h
	$(CC) $(CFLAGS) -c Player.c
	
UI.o: UI.c UI.h Deck.h vector.h Round.h Player.h Card.h ADTDefs.h
	$(CC) $(CFLAGS) -c UI.c
	
Round.o: Round.c Deck.h vector.h Round.h Player.h Card.h UI.h ADTDefs.h
	$(CC) $(CFLAGS) -c Round.c
	
main.o: main.c Game.h ADTDefs.h
	$(CC) $(CFLAGS) -c main.c
	
clean:
	rm -f $(TARGET) $(OBJS)
