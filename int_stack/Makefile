#
# Makefile for Assignment 03 template code.
#

CC = gcc
CFLAGS = -g -Wall

# Default rule is to build executable named `driver`
default: driver

# Rule for building the executable.
driver: driver.c int_stack.o
	$(CC) $(CFLAGS) driver.c int_stack.o -o driver

# Rule for building int_stack.o, which depends on int_stack.c and int_stack.h.
int_stack.o: int_stack.c int_stack.h
	$(CC) $(CFLAGS) -c int_stack.c -o int_stack.o

clean:
	$(RM) driver
	$(RM) *.o

