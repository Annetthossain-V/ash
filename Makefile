
CXX = clang++
CXFLAGS := -Wall -Wextra -mtune=native -O2 -std=c++17

CC = clang
CFLAGS := -Wall -Wextra -mtune=native -O2 -std=c17 -Wno-unused-parameter

AS = clang 
ASFLAGS := 

LD = clang++
LDFLAGS := -O2

SRC_CXX := $(wildcard src/*.cxx)
SRC_C := $(wildcard src/*.c)
SRC_AS := $(wildcard src/*.s)

OBJ_CXX := $(patsubst src/%.cxx,%.o,$(SRC_CXX))
OBJ_C := $(patsubst src/%.c,%.o,$(SRC_C))
OBJ_AS := $(patsubst src/%.s,%.o,$(SRC_AS))

PNAME = ash

all: link clean

%.o: src/%.cxx
		$(CXX) $(CXFLAGS) -c $< -o $@

%.o: src/%.c 
		$(CC) $(CFLAGS) -c $< -o $@

%.o: src/%.s
		$(AS) $(ASFLAGS) -c $< -o $@

link: $(OBJ_C) $(OBJ_CXX) $(OBJ_AS)
		$(CXX) $(LDFLAGS) $(OBJ_C) $(OBJ_CXX) $(OBJ_AS) -o $(PNAME)

clean:
		rm -rf *.o


