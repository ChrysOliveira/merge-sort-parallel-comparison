CC = gcc
CFLAGS = -fopenmp -O2
SRC = $(wildcard *.c)
TARGET = main

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

run: $(TARGET)
	@echo "Running..."
	 ./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
