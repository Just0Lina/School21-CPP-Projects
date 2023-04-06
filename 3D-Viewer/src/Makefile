SRCE := s21_test.cpp 
CXX := g++ -std=c++17
CFLAGS := -Wall -Werror -Wextra
GCOV := -fprofile-arcs -ftest-coverage
OS := $(shell uname)
DIR := build
NAME := 3D_Viewer_v2.0
ifeq ($(OS), Linux)
	LIBS=-lgtest -g -lgtest_main -lpthread
	LEAKS= valgrind --leak-check=full
else
	LIBS=-lgtest
	LEAKS=CK_FORK=no leaks --atExit --
endif

all: clean build

build:
	mkdir -p $(DIR); cd $(DIR); qmake ../; make; rm -rf *.h *.cpp *.ui *.o *.qrc Makefile

install: build
	mkdir $(HOME)/Desktop/$(NAME)/
	cp -rf $(DIR)/3DViewer_v2.app $(HOME)/Desktop/$(NAME)/
	make clean

uninstall:
	rm -rf $(HOME)/Desktop/$(NAME)/

dvi:
	open -a "Google Chrome" ./html/description.html

dist:
	rm -rf archive_v2
	mkdir archive_v2
	cp Makefile *.cpp *.h archive_v2/
	cp -a QT archive_v2
	cp -a html archive_v2
	tar -cvzf $(HOME)/Desktop/archive_v2.tgz archive_v2/
	rm -rf archive_v2/

tests: clean
	$(CXX) $(CFLAGS) $(SRCE) model/model.cpp controller/controller.cpp -o model_test.out $(LIBS)
	./model_test.out

gcov_report:
	$(CXX) $(GCOV) s21_test.cpp model/model.cpp $(LIBS) -o GCOV_test.out
	./GCOV_test.out
	lcov -t "GCOV_test" -o GCOV_test.info -c -d . --no-external
	genhtml -o ./report GCOV_test.info
	open -a "Google Chrome" report/index.html

leaks:
	CK_FORK=no leaks --atExit -- ./model_test.out

check_clang:
	@cp ../materials/linters/.clang-format .clang-format
	@clang-format -i *.cpp *.h
	@rm -rf .clang-format

clean:
	rm -rf *.o *.a *.gcno *.gcda *.info *.out *.dSYM
	rm -rf ./report
	rm -rf ./build
	rm -rf ./Documentation
	rm -rf $(HOME)/Desktop/$(NAME)_archive.tgz

.PHONY: all install uninstall clean dvi dist tests gcov_report lint leaks
