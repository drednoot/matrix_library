CXX=gcc -lstdc++
FLAGS=-Wall -Werror -Wextra -std=c++17
GTEST=-lgtest
GCOVFLAGS=--coverage
DEBUG=-DDEBUG -g
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	OPEN_CMD = xdg-open
endif

ifeq ($(UNAME_S),Darwin)
	OPEN_CMD = open
endif

all: my_matrix_oop.a test gcov

my_matrix_oop.a: my_matrix_oop.o
	ar rcs my_matrix_oop.a my_matrix_oop.o

my_matrix_oop.o: my_matrix_oop.cc
	$(CXX) $(FALGS) $(GTEST) $(DEBUG) $(GCOVFLAGS) -c my_matrix_oop.cc

build_test: my_matrix_oop.a
	$(CXX) $(FLAGS) $(DEBUG) $(GCOVFLAGS) tests.cc $(GTEST) my_matrix_oop.a -o test

main: my_matrix_oop.a
	$(CXX) $(FLAGS) $(GTEST) $(DEBUG) $(GCOVFLAGS) my_matrix_oop.a main.cpp -o main

test: build_test
	./test

gcov: build_test
	./test
	rm -rf tests.gcda tests.gcno
	geninfo . -b . -o ./coverage.info
	genhtml coverage.info -o gcov_report
	$(OPEN_CMD) gcov_report/index.html

clean:
	rm -rf *.o
	rm -rf *.a
	rm -rf *.dSYM
	rm -rf test
	rm -rf *.gcda *gcno *.info gcov_report/
