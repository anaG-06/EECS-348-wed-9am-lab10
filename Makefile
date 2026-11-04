CC = g++
Cflags = -Wall -Wextra -Wpedantic -Werror

all: program

program: main.cpp
	$(CC) $(Cflags) main.cpp -o main

clean:
	rm -f main program