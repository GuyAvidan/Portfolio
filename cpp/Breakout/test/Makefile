CXX?=g++
CC=$(CXX)

CPPFLAGS = -MMD -MP

CXXFLAGS = -std=c++17
CXXFLAGS+= -pedantic -Wall -g
#CXXFLAGS+= -Werror

CPPFLAGS += -I$(INC_DIR) $(LDLIBS)

LDLIBS   = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SRC_DIR = ../src
INC_DIR = ../inc

TARGET = utest
OBJECTS = utest.o $(SRC_DIR)/game.o $(SRC_DIR)/normalBrick.o $(SRC_DIR)/paddle.o $(SRC_DIR)/ball.o 
OBJECTS += $(SRC_DIR)/abstractBrick.o $(SRC_DIR)/hardBrick.o $(SRC_DIR)/unbreakableBrick.o 
OBJECTS += $(SRC_DIR)/level.o  $(SRC_DIR)/score.o $(SRC_DIR)/text.o $(SRC_DIR)/explodingBrick.o $(SRC_DIR)/bonusBrick.o
OBJECTS += $(SRC_DIR)/resManager.o

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
