
LIB_INC = /home/annetthossain/include/
LIB_DIR = /home/annetthossain/lib/

CXX = clang++
CXFLAGS := -Wall -Wextra -mtune=native -O0 -std=c++17 -I$(LIB_INC) -D_BUILD64XX -g 

CC = clang
CFLAGS := -Wall -Wextra -mtune=native -O0 -std=c17 -Wno-unused-parameter -g

LD = clang++
LDFLAGS := -O2 -L$(LIB_DIR) -lreadline -lncurses

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


