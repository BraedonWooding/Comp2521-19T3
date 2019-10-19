CC = gcc
CFLAGS = -Wall -Werror -std=c11 -g

all: polyfit difference list.o

list.o: list.c
polyfit: polyfit.c test_polyfit.c list.o
	$(CC) $(CFLAGS) -o polyfit polyfit.c test_polyfit.c list.o
difference: difference.c test_difference.c list.o
	$(CC) $(CFLAGS) -o difference difference.c test_difference.c list.o

clean:
	-rm *.o polyfit difference