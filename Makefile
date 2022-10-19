TARGET = ./build/program
CC = g++
FLAGS = -Wall -Werror -Wextra --std=c++2a

SRC = $(wildcard src/*.cpp)
OBJ = $(patsubst src/%.cpp, src/%.o, $(SRC))

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

rebuild: clean all

clean:
	rm $(TARGET) src/*.o

clean_o:
	rm src/*.o%
