CC = cc
CFLAGS = -Wall -std=c11 -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -lraylib -lm -lpthread -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo

TARGET = mazeVisualization
SRCS = main.c

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)