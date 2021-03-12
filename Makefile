CC=g++
CFLAGS=-Wall -Wextra -Wpedantic
CSTD=--std=c++20
COPT=-O3

DEPS=tic_tac_toe

CARGS=$(CSTD) $(CFLAGS) $(COPT)

$(DEPS): $(DEPS).cpp
	$(CC) $(DEPS).cpp -o $(DEPS) $(CARGS)


.PHONY: clean
clean:
	rm $(DEPS)

diss.asm: $(DEPS).cpp
	objdump -d $(DEPS) -M MISP > diss.asm


# -shared makes shared objects