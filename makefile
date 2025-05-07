CC = gcc
CFLAGS = -g -Wall
OBJ = hash_table.o
TARGET = HT8_2ADD
TEST_TARGET = test_hash

all: $(TARGET)

$(TARGET): main.o $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) main.o $(OBJ)

main.o: main.c hash_table.h
	$(CC) $(CFLAGS) -c main.c

hash_table.o: hash_table.c hash_table.h
	$(CC) $(CFLAGS) -c hash_table.c

# Unit test build
test: $(TEST_TARGET)

$(TEST_TARGET): test_hash.c $(OBJ)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) test_hash.c $(OBJ)

# Run unit test
run_test: test
	./$(TEST_TARGET)

# Clean
clean:
	rm -f *.o $(TARGET) $(TEST_TARGET)