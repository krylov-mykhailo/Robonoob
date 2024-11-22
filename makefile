CC = gcc
CFLAGS = -std=gnu99 -pedantic -Wall
TARGET = 7.2
OBJS = c_vector.o main.o

all: c_vector

c_vector: c_vector.o main.o
	$(CC) $(CFLAGS) -o c_vector c_vector.o main.o

c_vector.o: c_vector.c c_vector.h
	$(CC) $(CFLAGS) -c c_vector.c

main.o: main.c c_vector.h
	$(CC) $(CFLAGS) -c main.c


clean:
	rm -f *.o 7.2