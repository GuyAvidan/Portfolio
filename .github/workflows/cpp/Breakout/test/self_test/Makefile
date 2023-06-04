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

TARGET = main
OBJECTS = main.o

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
