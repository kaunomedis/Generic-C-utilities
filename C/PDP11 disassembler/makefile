# Modern Makefile for building disas11

CC      = gcc
CFLAGS  = -Wall -Wextra -O2 -g
OBJ     = deftbl.o disas.o disas11.o heapsort.o
TARGET  = disas11

all: $(TARGET)

$(TARGET): $(OBJ)
		$(CC) -o $(TARGET) $(OBJ)

%.o: %.c
		$(CC) $(CFLAGS) -c $<

clean:
		rm -f $(OBJ) $(TARGET)