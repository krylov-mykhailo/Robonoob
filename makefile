CC = cc
CFLAGS = -Wall -std=c11 -I. -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -lraylib -lm -lpthread -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo

TARGET = mazeVisualization
OBJS = main.o maze.o graph.o bfs.o dfs.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.c maze.h graph.h bfs.h dfs.h

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)