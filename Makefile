
LIB_INC = /home/annetthossain/include/
LIB_DIR = /home/annetthossain/lib/

BUILD_DIR = build

CXX = clang++
CXFLAGS := -Wall -Wextra -mtune=native -O0 -std=c++17 -I$(LIB_INC) -D_BUILD64XX -Wno-unused-parameter -g 

CC = clang
CFLAGS := -Wall -Wextra -mtune=native -O0 -std=c17 -Wno-unused-parameter -g

LD = clang++
LDFLAGS := -O2 -L$(LIB_DIR) -lreadline -lncurses

SRC_CXX := $(wildcard src/*.cxx)
SRC_C := $(wildcard src/*.c)

OBJ_CXX := $(patsubst src/%.cxx,%.o,$(SRC_CXX))
OBJ_C := $(patsubst src/%.c,%.o,$(SRC_C))

OBJ_BUILD_CXX = $(addprefix $(BUILD_DIR)/, $(OBJ_CXX))
OBJ_BUILD_C = $(addprefix $(BUILD_DIR), $(OBJ_C))

PNAME = ash

all: build link 

%.o: src/%.cxx
		$(CXX) $(CXFLAGS) -c $< -o $@
		mv $@ $(BUILD_DIR)/

%.o: src/%.c 
		$(CC) $(CFLAGS) -c $< -o $@
		mv $@ $(BUILD_DIR)/

build: $(OBJ_C) $(OBJ_CXX) link

link:
		$(CXX) $(LDFLAGS) $(OBJ_BUILD_C) $(OBJ_BUILD_CXX) -o $(PNAME)

clean:
		rm -rf *.o $(BUILD_DIR)/*.o


