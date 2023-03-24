CFLAGS = -Wall -Werror -Wextra -std=c11
ARCH = $(shell arch)
ifeq "$(ARCH)" "i386"
MYFLAGS = -lcheck -lpthread -lm  -I /usr/local/include -L/usr/local/lib
endif
ifeq "$(ARCH)" "x86_64"
MYFLAGS = -lcheck -lm -lpthread -lsubunit -g
endif

all: clean test gcov_report

dvi:
	open ../README.md

install:
	mkdir build
	cd build && qmake ../view/Calculator && make
	rm -rf build

dist: install
	tar -czf calc.tar.gz ~/Calc/Calculator
	rm -rf ~/Calc

uninstall:
	rm -rf ~/Calc

vpath %.c model:model/tests/ test

test: s21_SmartCalc.c s21_check_input.c s21_parser_and_sort.c test.c 
	gcc $^ -o $@ $(CFLAGS) $(MYFLAGS) --coverage

gcov_report: test
	./test
	gcovr --html-details rep.html
	open rep.html

check:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -i model/*.c
	clang-format -i model/tests/*.c
	clang-format -i model/*.h
	clang-format -i view/Calculator/*.cpp
	clang-format -i view/Calculator/*.h

clean:
	rm -rf *.o *.gcda *.a *.html *.gcno *.css .clang-format build 
	rm -f test
	rm -rf *.tar.gz
	rm -rf view/Calculator/*.o

rebuild: clean all
