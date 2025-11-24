CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = gemini-parser
SRC = gemini-parser.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET) file.gmi

.PHONY: all clean run
