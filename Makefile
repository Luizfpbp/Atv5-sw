# Flags
CC = gcc

make: matrix.c
	$(CC) -pthread $< -o $@

.PHONY: run clean

run: 
	./make

clean:
	rm make
