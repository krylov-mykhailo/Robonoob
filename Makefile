CC = gcc
PATH_TO_HASH = ../hash
CFLAGS = -Wall -Wextra -O2 -g -I$(PATH_TO_HASH) -I.

TARGET = main
TEST_TARGET = test_hash

INTERFACE = hash_table
IMPL = linear_probing_impl

VPATH = $(PATH_TO_HASH)

COMMON_OBJS = $(IMPL).o hash_code.o
MAIN_OBJS = $(TARGET).o $(COMMON_OBJS)
TEST_OBJS = test_hash.o $(COMMON_OBJS)

all: $(TARGET) $(TEST_TARGET)

# Main binary
$(TARGET): $(MAIN_OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(MAIN_OBJS)

$(TARGET).o: $(TARGET).c $(INTERFACE).h
	$(CC) $(CFLAGS) -c $(TARGET).c

# Test binary
$(TEST_TARGET): $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_OBJS)

test_hash.o: test_hash.c $(INTERFACE).h
	$(CC) $(CFLAGS) -c test_hash.c -o test_hash.o

# Common object files
$(IMPL).o: $(PATH_TO_HASH)/$(IMPL).c $(INTERFACE).h item.h
	$(CC) $(CFLAGS) -c $(PATH_TO_HASH)/$(IMPL).c -o $(IMPL).o

hash_code.o: $(PATH_TO_HASH)/hash_code.c $(PATH_TO_HASH)/hash_code.h
	$(CC) $(CFLAGS) -c $(PATH_TO_HASH)/hash_code.c -o hash_code.o

clean:
	rm -f $(TARGET) $(TEST_TARGET) *.o test_hash.o
	rm -f $(IMPL).o hash_code.o
test: $(TEST_TARGET)
	./$(TEST_TARGET)