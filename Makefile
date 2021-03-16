.PHONY: clean check run help build syntax
.DEFAULT_GOAL := run

### FILE STRUCTURE ###
BASEDIR = .
BUILDDIR = $(BASEDIR)/build

BUILDSRC = $(BUILDDIR)/src
BUILDAPP = $(BUILDDIR)/main
BUILDTEST = $(BUILDDIR)/test

LIBDIR = $(BASEDIR)/libs
SRCDIR = $(BASEDIR)/src
TESTDIR = $(BASEDIR)/tests

LIBFILES = $(wildcard $(LIBDIR)/*.cpp)
LIBHEADERS = $(wildcard $(LIBDIR)/*.hpp)

SRCFILES = $(wildcard $(SRCDIR)/*.cpp)
TESTFILES = $(wildcard $(TESTDIR)/*.cpp)

OBJ_FILES := $(patsubst $(LIBDIR)/%.cpp,$(BUILDSRC)/%.o,$(LIBFILES))
SRC_FILES := $(patsubst $(SRCDIR)/%.cpp,$(BUILDAPP)/%.o,$(SRCFILES))
TEST_FILES := $(patsubst $(TESTDIR)/%.cpp,$(BUILDTEST)/%.o,$(TESTFILES))


### COMPILER FLAGS ###
CC=clang++
LDFLAGS=
CPPFLAGS=--std=c++20 -I./libs
CXXFLAGS:=$(CXXFLAGS) -Werror -Wall -Wextra -Wconversion -Wunreachable-code -Wuninitialized -pedantic-errors -Wold-style-cast -Wno-error=unused-variable

ifdef DBG_FLAG
	CXXFLAGS := $(CXXFLAGS) -g
else
	CXXFLAGS := $(CXXFLAGS) -O3
endif



### PROJECT
PROJECT = tic_tac_toe
TEST = test

build: $(PROJECT)


run: $(PROJECT)
	./$(PROJECT)

check: $(TEST)
	./$(TEST)

clean:
	rm -f $(BUILDSRC)/*.o $(BUILDAPP)/*.o $(BUILDTEST)/*.o $(TEST) $(PROJECT)

summary:
	wc -l libs/* src/*

help:
	@echo "** HELP **"
	@echo "make run: build && run program"
	@echo "make check: build && run test"
	@echo "make summary: count number of lines in libs and src"
	@echo "make build: combile project"
	@echo "make clean: remove all object files"


### TUTORIAL ON MAKE
# This is how Makefile works
# all: library.cpp main.cpp
# $@ evaluates to all
# $< evaluates to library.cpp
# $^ evaluates to library.cpp main.cpp

# build project
$(PROJECT): $(SRC_FILES) $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $@ $^

# build test
$(TEST): $(TEST_FILES) $(OBJ_FILES)
	$(CC) -lgtest $(LDFLAGS) -o $@ $^


# build lib objects
$(BUILDSRC)/%.o: $(LIBDIR)/%.cpp $(LIBHEADERS)
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

# build main object
$(BUILDAPP)/%.o: $(SRCDIR)/%.cpp $(LIBHEADERS)
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

# build test object
$(BUILDTEST)/%.o: $(TESTDIR)/%.cpp $(LIBHEADERS)
	$(CC) -lgtest $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<