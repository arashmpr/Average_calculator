CC = g++
FLAGS = -std=c++11
COMPILE_FLAGS = $(FLAGS) -c

all: main.out class.out student.out read_and_calculate.out

main.out: main.o utils.o
	$(CC) main.o utils.o $(FLAGS) -o main.out

class.out: class.o utils.o
	$(CC) class.o utils.o $(FLAGS) -o class.out

student.out: student.o utils.o
	$(CC) student.o utils.o $(FLAGS) -o student.out

read_and_calculate.out: read_and_calculate.o utils.o
	$(CC) read_and_calculate.o utils.o $(FLAGS) -o read_and_calculate.out

utils.o: utils.cpp utils.hpp
	$(CC) $(COMPILE_FLAGS) utils.cpp

.PHONY: clean

clean:
				rm *.o
				rm *.out