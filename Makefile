# makefile - program for cs iii - hw 4 - ibraheem

all: tct # note to remember: run using this "./tct"

tct: TimeCode.o TimeCodeTests.o
	g++ -o tct TimeCode.o TimeCodeTests.o

TimeCode.o: TimeCode.cpp TimeCode.h
	g++ -c TimeCode.cpp

TimeCodeTests.o: TimeCodeTests.cpp TimeCode.h
	g++ -c TimeCodeTests.cpp

clean: # make clean "to clean"
	rm -f *.o tct
