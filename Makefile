# Makefile - program - HW 4 - Ibraheem

CC = g++
CFLAGS = -g -Wall -std=c++11

all: tct nasa pdt

# TimeCode Test Program
tct: TimeCode.o TimeCodeTests.o
	$(CC) $(CFLAGS) -o tct TimeCode.o TimeCodeTests.o

# NASA Launch Analysis Program
nasa: TimeCode.o NasaLaunchAnalysis.o
	$(CC) $(CFLAGS) -o nasa TimeCode.o NasaLaunchAnalysis.o

# Paint Dry Timer Program
pdt: TimeCode.o PaintDryTimer.o
	$(CC) $(CFLAGS) -o pdt TimeCode.o PaintDryTimer.o

# Object files
TimeCode.o: TimeCode.cpp TimeCode.h
	$(CC) $(CFLAGS) -c TimeCode.cpp

TimeCodeTests.o: TimeCodeTests.cpp TimeCode.h
	$(CC) $(CFLAGS) -c TimeCodeTests.cpp

NasaLaunchAnalysis.o: NasaLaunchAnalysis.cpp TimeCode.h
	$(CC) $(CFLAGS) -c NasaLaunchAnalysis.cpp

PaintDryTimer.o: PaintDryTimer.cpp TimeCode.h
	$(CC) $(CFLAGS) -c PaintDryTimer.cpp

# Cleanup
clean:
	rm -f *.o tct nasa pdt

.PHONY: all clean # just learned that