


CC = gcc
CFLAGS=-g -Wall -std=c89 -pedantic-errors
TARGET = gooseBoardGame
all: $(TARGET)
$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	rm $(TARGET)
