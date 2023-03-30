OS=$(shell uname)
ifeq ($(OS), Linux)
	CXXFLAGS=-lgtest -g  -lpthread
	LEAKS = valgrind --leak-check=full
else
	CXXFLAGS = -lgtest -g
	LEAKS = CK_FORK=no leaks --atExit --
endif

CXX=g++ -std=c++17
SUBDIRS =  s21_map s21_multiset s21_set  s21_list s21_vector s21_stack  s21_queue s21_array

all: gcov_report check

tests: clean $(SUBDIRS)


$(SUBDIRS): clean
	@$(CXX) --coverage -O0 -C $@/$@_tests.cpp -o $@_tests $(CXXFLAGS)
	$(LEAKS) ./$@_tests

	

small_report:
	lcov -t "gcov_report" --no-external -o small.info -c -d .
	genhtml -o small_report small.info
	@open -a "Safari" small_report/index.html

gcov_report: tests
	lcov -t "gcov_report" --no-external -o all_tests.info -c -d .
	genhtml -o all_report all_tests.info
	# @open -a "Safari" all_report/index.html

clean:
	rm -rf *.gcda *.gcno *.o *.info *_tests */*.out */*.dSYM all_report

check:
	@clang-format -i s21_*/*.tpp s21_*/*.h
	clang-format -n s21_*/*.tpp s21_*/*.h
	cppcheck --enable=all  --language=c++ --suppress=postfixOperator \
	--suppress=negativeIndex --suppress=knownConditionTrueFalse \
	--suppress=publicAllocationError --suppress=duplicateExpression \
	--suppress=internalAstError \
	--suppress=unusedFunction --suppress=unmatchedSuppression s21_*/* 
	
 
.PHONY:  check clean_gcov gcov_report tests $(SUBDIRS)
