CC = g++
FLAGS = -std=c++17 -Wall
EXEC = tests.out

all: allocator.o

allocator.o: allocator.cpp
	$(CC) $(FLAGS) -c allocator.cpp

test: allocator.o $(EXEC)
	./$(EXEC)

tests.o: tests.cpp
	$(CC) $(FLAGS) -c tests.cpp

$(EXEC): tests.o
	$(CC) $(FLAGS) allocator.o tests.o -o $(EXEC)

clean:
	rm -f allocator.o tests.o $(EXEC)
