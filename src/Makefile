CFLAGS= -Wall -o -g -fPIC

all: tester mathlib

tester: tester/*.cpp
		cc -o tester.out -g tester/*.cpp -ldl -lstdc++

mathlib: mathlib/*.cpp
		cc mathlib/*.cpp -o mathlib.so -shared -fPIC 