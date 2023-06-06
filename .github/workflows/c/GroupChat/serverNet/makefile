#makefile ClientManager

TARGET = MainServerManager.out
CC = gcc
CFLAGS = -ansi -g -pedantic
OBJS = ServerManager.o serverNet.o userManager.o user.o protocol.o group.o groupManager.o IPpool.o
#LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/guy/prog/GENDS/ 
#export LD_LIBRARY_PATH


$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) -L/home/guy/prog/GENDS -lgends

serverNet.o:serverNet.c serverNet.h  
	$(CC) $(CFLAGS) -c serverNet.c 

ServerManager.o:ServerManager.c  ../protocol/protocol.h 
	$(CC) $(CFLAGS) -c ServerManager.c 

userManager.o: userM/userManager.c userM/userManager.h
	$(CC) $(CFLAGS) -c userM/userManager.c 

user.o: userM/user.c userM/user.h
	$(CC) $(CFLAGS) -c userM/user.c 

groupManager.o: groupM/groupManager.c groupM/groupManager.h
	$(CC) $(CFLAGS) -c groupM/groupManager.c 

group.o: groupM/group.c groupM/group.h
	$(CC) $(CFLAGS) -c groupM/group.c 

IPpool.o: pool_ip/IPpool.c pool_ip/IPpool.h
	$(CC) $(CFLAGS) -c pool_ip/IPpool.c 

protocol.o: ../protocol/protocol.c  ../protocol/protocol.h 
	$(CC) $(CFLAGS) -c ../protocol/protocol.c 
	
debug: $(TARGET)
	gdb ./$(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)

