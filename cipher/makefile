#My attempt at splitting up my code
# if this doesn't work, my 3rd should work
CC = gcc
CFLAGS	=-g -Wall

default: cipher

cipher: cipher.c vin.h vin.o caesar.h caesar.o
	$(CC) $(CFLAGS) cipher.c vin.o caesar.o -o cipher
caesar.o: caesar.h caesar.c
	$(CC) $(CFLAGS) caesar.c -c -o caesar.o
vin.o: vin.h vin.c
	$(CC) $(CFLAGS) vin.c -c -o vin.o
clean:
	%(RM)cipher
	$(RM)*.0
