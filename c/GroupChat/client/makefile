#makefile ClientManager

TARGET = MainClientManager.out
CC = gcc
CFLAGS = -ansi -g -pedantic
OBJS = Client_manager.o MainClientManager.o UI.o ClientNet.o protocol.o
#LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/guy/prog/GENDS/ 
#export LD_LIBRARY_PATH


$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) -L/home/guy/prog/GENDS -lgends

MainClientManager.o:MainClientManager.c Client_manager.h ../protocol/protocol.h
	$(CC) $(CFLAGS) -c MainClientManager.c 
	
ClientManager.o:Client_manager.c Client_manager.h ../protocol/protocol.h ClientNet.h UI.h 
	$(CC) $(CFLAGS) -c Client_manager.c 

protocol.o: ../protocol/protocol.c  ../protocol/protocol.h 
	$(CC) $(CFLAGS) -c ../protocol/protocol.c 
	
ClientNet.o:ClientNet.c ClientNet.h UI.h ../protocol/protocol.h
	$(CC) $(CFLAGS) -c ClientNet.c 
	
UI.o:UI.c UI.h
	$(CC) $(CFLAGS) -c UI.c 

debug: $(TARGET)
	gdb ./$(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)
