CC=gcc
CXX=g++
CFLAGS=-Iinclude -Wall -Wextra -std=c11
CXXFLAGS=-Iinclude -Wall -Wextra -std=c++17
LDFLAGS=-lcurl

SRC_C=$(wildcard src/*.c)
SRC_CPP=$(wildcard src/*.cpp)
OBJ_C=$(SRC_C:.c=.o)
OBJ_CPP=$(patsubst %.cpp,%.cpp.o,$(SRC_CPP))

all: libai_sdk.a example_c example_cpp
libai_sdk.a: $(OBJ_C) $(OBJ_CPP)
	ar rcs $@ $^

example_c: examples/example.c libai_sdk.a
	$(CC) $(CFLAGS) -o $@ $< libai_sdk.a $(LDFLAGS)

example_cpp: examples/example.cpp libai_sdk.a
	$(CXX) $(CXXFLAGS) -o $@ $< libai_sdk.a $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.cpp.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJ_C) $(OBJ_CPP) libai_sdk.a example_c example_cpp

