CC = gcc
CFLAGS = -Wall -lm

all: build

build: 
	$(CC) -o tema1 TetriBit.c $(CFLAGS)

run: 
	./tema1 

clean: 
	rm -f tema1
