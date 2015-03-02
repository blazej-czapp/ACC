all:
	@clang++ -std=c++11 -o test -Isrc $(wildcard *.cpp)
	@./test