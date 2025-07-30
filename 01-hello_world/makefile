# Makefile for compiling our "Hello" Motif application
# Run `make` to build the application.
# Run `make clean` to remove the compiled files.
CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -lXm -lXt -lX11
TARGET = out/hello
SRC = hello.c

all: $(TARGET)

$(TARGET): $(SRC)
	mkdir -p out
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

# To remove the "out" directory, add "rm -rf out" to the clean target.
clean:
	rm -f $(TARGET) *.o
