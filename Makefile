CC = gcc
CFLAGS = -g -std=gnu99
BUILD_DIR = cmake-build-debug

all: $(BUILD_DIR)/HT7

$(BUILD_DIR)/HT7: $(BUILD_DIR)/llrb.o $(BUILD_DIR)/test_llrb.o $(BUILD_DIR)/bst_check.o
	$(CC) $^ -o $@

$(BUILD_DIR)/llrb.o: llrb.c llrb.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/test_llrb.o: test_llrb.c llrb.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/bst_check.o: bst_check.c llrb.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/HT7