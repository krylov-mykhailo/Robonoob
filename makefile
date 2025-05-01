CC = gcc
CFLAGS = -Wall -Wextra -std=c11

OBJS = graph.o queue.o paths.o paths_helper.o bfs.o bfs_shortest.o test_bfs.o

all: test_bfs

test_bfs: $(OBJS)
	$(CC) $(CFLAGS) -o test_bfs $(OBJS)

clean:
	rm -f *.o test_bfs