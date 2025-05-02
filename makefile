CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
TARGET = topo_sort
SRC = main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)