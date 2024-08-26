CC = g++
CFLAGS = -std=c++17 -Wall -Werror -Wextra
OS = $(shell uname)
ifeq ($(OS), Linux)
	FLAGS = -lgmock -lgtest -pthread
else 
	FLAGS = -lgtest
endif

all: install

install: uninstall
	@mkdir -p ./build
	@qmake6 ./SmartCalc/SmartCalc.pro -o ./build/Makefile
	@cd ./build; make > /dev/zero 2> /dev/zero
	@mkdir -p ~/Applications ; cp -r ./build/SmartCalc.app ~/Applications/SmartCalc.app

uninstall: clean
	@rm -rf ./build
	@rm -rf ~/Applications/SmartCalc.app

test: clean
	$(CC) $(CFLAGS) ./SmartCalc/model.cc test.cc -o test $(FLAGS)
	./test

clean:
	@rm -rf *.out *.o *.a a.out.dSYM *.log
	@rm -rf *.gcda *.gcno *.info test
	@rm -rf test.dSYM
	@rm -rf build-SmartCalc-Desktop_x86_darwin_generic_mach_o_64bit-Debug

style:
	clang-format -style=google -n SmartCalc/*.cpp SmartCalc/*.h SmartCalc/*.cc

dist:
	cd .. && tar -czvf SmartCalc.tar src

dvi:
	open dvi.html

leaks: test
ifeq ($(OS), Linux)
	CK_FORK=no valgrind --leak-check=full -s --track-origins=yes --log-file=leak.log ./test
	cat leak.log
	@make clean
else 
	CK_FORK=no leaks -atExit -- ./test
	@make clean
endif
