# makefile sample

TARGET= libgends.so
CC= gcc
CFLAGS= -ansi -g -pedantic -Wall -fPIC
DNCFLAGS= -ansi -g -pedantic -Wall -shared
OBJS=  GenList.o list_itr.o list_functions.o GenVector.o GenHeap.o GenQueue.o HashMap.o

$(TARGET): $(OBJS)
	$(CC) $(DNCFLAGS) -o $(TARGET) $(OBJS)
	
GenList.o: GenList.c ListInternal.h GenList.h
	$(CC) $(CFLAGS) -c GenList.c

list_itr.o: list_itr.c list_itr.h ListInternal.h GenList.h
	$(CC) $(CFLAGS) -c list_itr.c
	
list_functions.o: list_functions.c list_itr.h ListInternal.h list_functions.h
	$(CC) $(CFLAGS) -c list_functions.c
	
GenVector.o: GenVector.c GenVector.h
	$(CC) $(CFLAGS) -c GenVector.c

GenHeap.o: GenHeap.c GenHeap.h GenVector.h 
	$(CC) $(CFLAGS) -c GenHeap.c
	
GenQueue.o: GenQueue.c GenQueue.h
	$(CC) $(CFLAGS) -c GenQueue.c
	
HashMap.o: HashMap.c HashMap.h list_itr.h ListInternal.h list_functions.h GenList.h
	$(CC) $(CFLAGS) -c HashMap.c

clean:
	rm -f $(TARGET) $(OBJS)
