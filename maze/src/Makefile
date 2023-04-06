SRCE := Maze_ZhMZh/tests/test.cpp 
CXX := g++ -std=c++17
CFLAGS := -Wall -Werror -Wextra
GCOV := -fprofile-arcs -ftest-coverage
OS := $(shell uname)
DIR := build
ARCH := archive_A1_ZhMZh
NAME := MAZE
ifeq ($(OS), Linux)
	LIBS=-lgtest -g -lgtest_main -lpthread
	LEAKS= valgrind --leak-check=full
else
	LIBS=-lgtest
	LEAKS=CK_FORK=no leaks --atExit --
endif

all: clean build

build: clean
	mkdir -p $(DIR)
	cp -r Maze_ZhMZh/* $(DIR)
	cd $(DIR); qmake; make
	cd $(DIR); rm -rf *.h *.cpp *.ui *.o *.qrc .qmake.stash Makefile *.pro *.user clang-format ./img ./tests ./Controller ./Model ./View

install: build
	mkdir $(HOME)/Desktop/$(NAME)/
	cp -rf $(DIR)/Maze_ZhMZh.app $(HOME)/Desktop/$(NAME)/
	make clean

uninstall:
	rm -rf $(HOME)/Desktop/$(NAME)/

dvi:
	open -a "Google Chrome" ./html/description.html

dist:
	rm -rf $(ARCH)
	mkdir $(ARCH)
	cp Makefile $(ARCH)/
	cp -a html $(ARCH)
	cp -a Maze_ZhMZh $(ARCH)
	tar -cvzf $(HOME)/Desktop/$(ARCH).tgz $(ARCH)/
	rm -rf $(ARCH)/

tests: clean
	$(CXX) $(CFLAGS) $(SRCE) Maze_ZhMZh/Model/maze.cpp Maze_ZhMZh/Model/cave.cpp -o test.out $(LIBS)
	./test.out

gcov_report:
	$(CXX) $(GCOV) $(SRCE) Maze_ZhMZh/Model/maze.cpp Maze_ZhMZh/Model/cave.cpp $(LIBS) -o GCOV_test.out
	./GCOV_test.out
	lcov -t "GCOV_test" -o GCOV_test.info -c -d . --no-external
	genhtml -o ./report GCOV_test.info
	open -a "Google Chrome" report/index.html

leaks: tests
	CK_FORK=no leaks --atExit -- ./test.out

check_clang:
	@cp ../materials/linters/.clang-format ./Maze_ZhMZh/Model/.clang-format 
	@cp ../materials/linters/.clang-format ./Maze_ZhMZh/Controller/.clang-format 
	@cp ../materials/linters/.clang-format ./Maze_ZhMZh/View/.clang-format
	@clang-format -i ./Maze_ZhMZh/Model/*.cpp ./Maze_ZhMZh/Model/*.h 
	@clang-format -i ./Maze_ZhMZh/View/*.cpp ./Maze_ZhMZh/View/*.h 
	@clang-format -i ./Maze_ZhMZh/Controller/*.cpp ./Maze_ZhMZh/Controller/*.h
	@rm -rf ./Maze_ZhMZh/Model/.clang-format
	@rm -rf ./Maze_ZhMZh/View/.clang-format
	@rm -rf ./Maze_ZhMZh/Controller/.clang-format

clean:
	rm -rf *.o *.a *.gcno *.gcda *.info *.out *.dSYM build* .qmake.stash
	rm -rf ./report
	rm -rf ./build
	rm -rf ./Documentation
	rm -rf $(HOME)/Desktop/$(NAME)_archive.tgz
	rm -rf *.app

.PHONY: all install uninstall clean dvi dist tests gcov_report lint leaks
