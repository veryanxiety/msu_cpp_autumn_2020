CC = g++
FLAGS = -std=c++17 -Wall
EXEC = tests.out

all: tokenparser.o

tokenparser.o: tokenparser.cpp
	$(CC) $(FLAGS) -c tokenparser.cpp

test: tokenparser.o $(EXEC)
	./$(EXEC)

tests.o: tests.cpp
	$(CC) $(FLAGS) -c tests.cpp

$(EXEC): tests.o
	$(CC) $(FLAGS) tokenparser.o tests.o -o $(EXEC)

clean:
	rm -f tokenparser.o tests.o $(EXEC)
