TARGET = HT8_2

SRCS = main.c hash_table.c

HEADERS = hash_table.h

OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -g -Wall

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

all: $(TARGET)