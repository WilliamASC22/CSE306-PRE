# Makefile format from LEX07

# OS identification from: https://stackoverflow.com/questions/714100/os-detecting-makefile
OS := $(shell uname -s)

ifeq ($(OS), Darwin) 
  INCLUDE_PATH := /opt/homebrew/Cellar/criterion/2.4.1_1/include
  LIB_PATH := /opt/homebrew/Cellar/criterion/2.4.1_1/lib
endif
ifeq ($(OS), Linux) 
  INCLUDE_PATH := /util/criterion/include
  LIB_PATH := /util/criterion/lib/x86_64-linux-gnu
endif

CC = gcc
CFLAGS = -Wall -std=c11
DEBUG = -g

csv.o: csv.h csv.c
	$(CC) -c $(DEBUG) $(CFLAGS) csv.c

tests.o: tests.c code.h
	$(CC) -c $(DEBUG) $(CFLAGS) -I $(INCLUDE_PATH) tests.c

tests:  csv.o tests.o
	$(CC) $(DEBUG) $(CFLAGS) -L $(LIB_PATH) -I $(INCLUDE_PATH) -o tests csv.o tests.o -lcriterion

clean:
	rm -rf *~ *.o tests csv *.dSYM
