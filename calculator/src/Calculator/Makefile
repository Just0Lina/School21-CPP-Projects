OS=$(shell uname)
ifeq ($(OS), Linux)
	CXXFLAGS=-lgtest -g -lgtest_main -lpthread
	LEAKS = valgrind --leak-check=full
else
	CXXFLAGS = -lgtest -g
	LEAKS = CK_FORK=no leaks --atExit --
endif


CXX=g++ -std=c++17

all: build gcov_report check

build: clean
	-mkdir build
	-cp *.h *.cpp *.ui *.pro *.png *.ico Makefile ./build
	-cd build; qmake Calculator.pro
	-cd build; make
	-cd build; rm -rf *.h *.cpp *.ui *.pro *.png *.ico Makefile *.o


install: build
	cp -r build/Calculator.app $(HOME)/Applications

uninstall:
	rm -rf  $(HOME)/Applications/Calculator.app

tests: clean
	${CXX} --coverage -O0 -C CalculatorTests.cpp CalculatorModel.cpp CreditModel.cpp -o test $(CXXFLAGS)
	@$(LEAKS) ./test


gcov_report: tests
	lcov -t "gcov_report" --no-external -o all_tests.info -c -d .
	genhtml -o all_report all_tests.info
	# @open -a "Safari" all_report/index.html



clean:
	rm -rf *.gcda *.gcno *.o *.info *_tests */*.out *.dSYM all_report build test

check:
	@clang-format -i *.h *.cpp
	@clang-format -n *.h *.cpp
	


dist: build
	tar -cvf Calculator.tar build


dvi: 
	open -a "Google Chrome" description.html

 
.PHONY:  check clean_gcov gcov_report tests $(SUBDIRS)
