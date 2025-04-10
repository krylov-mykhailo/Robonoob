
CC = gcc
CFLAGS = -g -Wall -Wextra -std=c99

# Файли
SRC = main.c bst.c
OBJ = $(SRC:.c=.o)
TARGET = bst

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

valgrind: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)
