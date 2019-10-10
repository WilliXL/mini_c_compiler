CC=g++

all: src_c/lex.cpp src_c/lex.hpp
	$(CC) -g -Wall -o mcc src_c/lex.cpp src_c/lex.hpp

clean:
	$(RM) mcc