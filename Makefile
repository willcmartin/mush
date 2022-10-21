CC = gcc
CFLAGS  = -g -Wall
TARGET = mush

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o bin/$(TARGET) $(TARGET).c

clean:
	$(RM) $(TARGET)