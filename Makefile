CC=g++

all: src_c/generate.cpp src_c/parse.cpp src_c/lex.cpp
	$(CC) -g -Wall -o mcc src_c/generate.cpp src_c/parse.cpp src_c/lex.cpp

clean:
	$(RM) mcc