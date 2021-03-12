CC=g++
CFLAGS=-Wall -Wextra -Wpedantic
CSTD=--std=c++20
COPT=-O3
SRC=src

OBS=src/board.cpp
DEPS=tic_tac_toe
HEADERS=src/game.hpp src/player.hpp

CARGS=$(CSTD) $(CFLAGS) $(COPT)

# build project
$(DEPS): $(SRC)/$(DEPS).cpp $(HEADERS)
	$(CC) $(SRC)/$(DEPS).cpp $(OBS) -o $(DEPS) $(CARGS)


.PHONY: clean summary check
clean:
	rm $(DEPS)

# number of lines in src
summary:
	wc -l src/*

# check if can build
check: $(SRC)/$(DEPS).cpp $(HEADERS)
	$(CC) $(SRC)/$(DEPS).cpp $(OBS) $(CARGS) -fsyntax-only

# run tests
test: tests/main.cpp $(OBS)
	$(CC) tests/main.cpp -lgtest $(CARGS) $(OBS) -o test

# dissasemble program
diss.asm: $(DEPS).cpp
	objdump -d $(DEPS) -M MISP > diss.asm