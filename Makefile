CFLAGS=-O2 -fno-exceptions -std=c++14 -U_FORTIFY_SOURCE

all: error

gcc_main.o: gcc_main.cpp
	g++ -c gcc_main.cpp -o gcc_main.S -fPIC $(CFLAGS) -S
	g++ -c gcc_main.cpp -o gcc_main.o -fPIC $(CFLAGS)

clang_lib.o: clang_lib.cpp
	clang++ -c clang_lib.cpp -o clang_lib.S -fPIC -O2 -fno-exceptions -std=c++14 -U_FORTIFY_SOURCE -S -Xclang -ast-dump > clang.txt
	clang++ -c clang_lib.cpp -o clang_lib.S -fPIC $(CFLAGS) -S
	clang++ -c clang_lib.cpp -o clang_lib.o -fPIC $(CFLAGS)

error: clang_lib.o gcc_main.o
	g++ -c gcc_main.cpp -o gcc_main.S -fPIC -O2 -fno-exceptions -std=c++14 -U_FORTIFY_SOURCE -S -fdump-tree-all
	g++ clang_lib.o gcc_main.o -o error -fPIC -O2

.PHONY: clean
clean:
	rm -f *.o *.S error
	rm -f gcc_main.cpp.*
	rm clang.txt
