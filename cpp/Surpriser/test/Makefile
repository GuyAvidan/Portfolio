CXX?=g++
CC=$(CXX)

CPPFLAGS = -MMD -MP

CXXFLAGS = -std=c++20 -pedantic -Wall -g 
#CXXFLAGS+= -Werror

LDLIBS = -lpthread

CPPFLAGS += -I$(INC_DIR)

SRC_DIR = ../src
INC_DIR = ../inc

TARGET = utest

OBJECTS = utest.o $(SRC_DIR)/bell.o $(SRC_DIR)/joke.o $(SRC_DIR)/kaboom.o $(SRC_DIR)/surpriser.o 

check: $(TARGET)
	./$(TARGET) $(ARGS)

$(TARGET): $(OBJECTS) $(SRC_DIR)/bell.o $(SRC_DIR)/joke.o $(SRC_DIR)/kaboom.o $(SRC_DIR)/surpriser.o 

all: $(TARGET)

hell: $(TARGET)
	valgrind  --tool=helgrind ./$(TARGET)


stress: $(TARGET)
	@for number in $(shell seq 1 10) ; do \
		./$(TARGET) -v ; \
	done

valgrind:$(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=logV1.log ./$(TARGET)

clean:
	@$(RM) $(OBJECTS) $(DEPENDS) $(TARGET)

DEPENDS = $(OBJECTS:%.o=%.d)

