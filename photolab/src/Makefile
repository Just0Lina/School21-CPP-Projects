SRCE := PhotoBAB_v1/tests/tests.cpp 
CXX := g++  -std=c++17
CFLAGS := -std=gnu99  -Wall -Werror -Wextra
GCOV := -fprofile-arcs -ftest-coverage
OS := $(shell uname)blank
DIR := build
ARCH := archive_CPP8_PhotoBAB
NAME := PhotoBAB
ifeq ($(OS), Linux)
	LIBS= -lGLEW -lglfw -lGL -lm -lgtest -g -lgtest_main -lpthread 
	LEAKS= valgrind --leak-check=full
else
	LIBS=-lgtest -Qimage
	LEAKS=CK_FORK=no leaks --atExit --
endif

all: clean build

build: clean
	mkdir -p $(DIR)/PhotoBAB_v1
	mkdir -p $(DIR)/img
	cp -r PhotoBAB_v1/* $(DIR)
	cd $(DIR)/PhotoBAB_v1; qmake; make
	cd $(DIR)/PhotoBAB_v1; rm -rf *.h *.cpp *.ui *.o *.qrc .qmake.stash Makefile *.pro *.user clang-format ./tests ./Controller ./Model ./View

install: build
	mkdir $(HOME)/Desktop/$(NAME)/
	cp -rf $(DIR)/PhotoBAB_v1/PhotoBAB_v1.app $(HOME)/Desktop/$(NAME)/
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
	cp -a PhotoBAB_v1 $(ARCH)
	cp -a $(SRCE) $(ARCH)
	tar -cvzf $(HOME)/Desktop/$(ARCH).tgz $(ARCH)/
	rm -rf $(ARCH)/

tests: clean
	cd PhotoBAB_v1; cmake tests 
	cd PhotoBAB_v1; make
	cd PhotoBAB_v1; ./testing
	cd PhotoBAB_v1; rm -rf _deps bin cmake_install.cmake CMakeCache.txt CMakeFiles lib CTestTestfile.cmake Makefile

leaks:
	CK_FORK=no leaks --atExit -- ./PhotoBAB_v1/testing

check_clang:
	@cp ../materials/linters/.clang-format ./PhotoBAB_v1/PhotoBAB_v1/Model/.clang-format 
	@cp ../materials/linters/.clang-format ./PhotoBAB_v1/PhotoBAB_v1/Controller/.clang-format 
	@cp ../materials/linters/.clang-format ./PhotoBAB_v1/PhotoBAB_v1/View/.clang-format
	clang-format -i ./PhotoBAB_v1/PhotoBAB_v1/Model/*.cpp ./PhotoBAB_v1/PhotoBAB_v1/Model/*.h 
	clang-format -i ./PhotoBAB_v1/PhotoBAB_v1/View/*.cpp ./PhotoBAB_v1/PhotoBAB_v1/View/*.h 
	clang-format -i ./PhotoBAB_v1/PhotoBAB_v1/Controller/*.h
	@rm -rf ./PhotoBAB_v1/PhotoBAB_v1/Model/.clang-format
	@rm -rf ./PhotoBAB_v1/PhotoBAB_v1/View/.clang-format
	@rm -rf ./PhotoBAB_v1/PhotoBAB_v1/Controller/.clang-format


check:
	cppcheck --enable=all --suppress=missingInclude  --suppress=unusedFunction --std=c++17 --language=c++  ./PhotoBAB_v1/PhotoBAB_v1/*/*.cpp ./PhotoBAB_v1/PhotoBAB_v1/*/*.h

clean:
	rm -rf *.o *.a *.gcno *.gcda *.info *.out *.dSYM build* .qmake.stash
	rm -rf ./report
	rm -rf ./build
	rm -rf ./Documentation
	rm -rf $(HOME)/Desktop/$(NAME)_archive.tgz
	rm -rf *.app
	rm -rf  PhotoBAB_v1/.rcc  PhotoBAB_v1/testing*

.PHONY: all install uninstall clean dvi dist tests gcov_report lint leaks
