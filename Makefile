CC = g++
CFLAGS = -Werror -std=c++11

main: main.o database.o input.o
	$(CC) $(CFLAGS) -o main main.o database.o input.o

main.o: main.cpp database.h input.h
	$(CC) $(CFLAGS) -c main.cpp

database.o: database.cpp database.h
	$(CC) $(CFLAGS) -c database.cpp

input.o: input.cpp input.h database.h
	$(CC) $(CFLAGS) -c input.cpp

clean:
	rm -f *.o main

