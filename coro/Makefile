CC = gcc
CFLAGS = -Wall -I./src -I./lib

SRC_FILES = $(shell find . -name "*.[Sc]" ! -path "./example/*")
OBJ_FILES = $(SRC_FILES:%.o=.c)

.PHONY: clean

all: easy_coro easy_delay easy_ping_pong easy_io ping_pong fibonacci

easy_coro: $(OBJ_FILES) ./example/easy_coro.o
	$(CC) -o easy_coro $(OBJ_FILES) ./example/easy_coro.o $(CFLAGS)

easy_delay: $(OBJ_FILES) ./example/easy_delay.o
	$(CC) -o easy_delay $(OBJ_FILES) ./example/easy_delay.o $(CFLAGS)

easy_ping_pong: $(OBJ_FILES) ./example/easy_ping_pong.o
	$(CC) -o easy_ping_pong $(OBJ_FILES) ./example/easy_ping_pong.o $(CFLAGS)

easy_io: $(OBJ_FILES) ./example/easy_io.o
	$(CC) -o easy_io $(OBJ_FILES) ./example/easy_io.o $(CFLAGS)

ping_pong: $(OBJ_FILES) ./example/ping_pong.o
	$(CC) -o ping_pong $(OBJ_FILES) ./example/ping_pong.o $(CFLAGS)

fibonacci: $(OBJ_FILES) ./example/fibonacci.o
	$(CC) -o fibonacci $(OBJ_FILES) ./example/fibonacci.o $(CFLAGS)

clean:
	@rm -f ./example/*.o easy_coro easy_delay easy_ping_pong easy_io ping_pong fibonacci