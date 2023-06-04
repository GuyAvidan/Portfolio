CXX?=g++
CC=$(CXX)

CPPFLAGS = -MMD -MP

CXXFLAGS = -std=c++20
CXXFLAGS+= -pedantic -Wall -g
#CXXFLAGS+= -Werror

CPPFLAGS += -I$(INC_DIR) $(LDLIBS)

LDLIBS   = -lpthread

SRC_DIR = ../src
INC_DIR = ../inc

TARGET = utest
OBJECTS = utest.o $(SRC_DIR)/console.o $(SRC_DIR)/drone.o $(SRC_DIR)/protocol.o $(SRC_DIR)/client.o
OBJECTS += $(SRC_DIR)/server.o $(SRC_DIR)/telemetry.o

check: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJECTS)

all: $(TARGET)

valgrind:$(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=logV1.log ./$(TARGET)

clean:
	@$(RM) $(OBJECTS) $(DEPENDS) $(TARGET)

DEPENDS = $(OBJECTS:%.o=%.d)
-include $(DEPENDS)
