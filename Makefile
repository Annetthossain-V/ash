
CXX = clang++
CXFLAGS := -Wall -Wextra -mtune=native -O2 -std=c++17

CC = clang
CFLAGS := -Wall -Wextra -mtune=native -O2 -std=c17

LD = clang++
LDFLAGS := -O2

SRC_CXX := $(wildcard src/*.cxx)
SRC_C := $(wildcard src/*.c)

OBJ_CXX := $(patsubst src/%.cxx,%.o,$(SRC_CXX))
OBJ_C := $(patsubst src/%.c,%.o,$(SRC_C))

PNAME = ash

all: link clean

%.o: src/%.cxx
		$(CXX) $(CXFLAGS) -c $< -o $@

%.o: src/%.c 
		$(CC) $(CFLAGS) -c $< -o $@

link: $(OBJ_C) $(OBJ_CXX)
		$(CXX) $(LDFLAGS) $(OBJ_C) $(OBJ_CXX) -o $(PNAME)

clean:
		rm -rf *.o


