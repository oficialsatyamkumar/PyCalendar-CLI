CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = calendar

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) main.c -o $(TARGET)

clean:
	rm -f $(TARGET) *.o events.txt
