CXX = g++

CXXFLAGS = -O0 -g3 -std=c++17 

All: all
all: GenAlloc

GenAlloc: main.cpp FileParser.o Allocation.o 
	$(CXX) $(CXXFLAGS) main.cpp FileParser.o Allocation.o -o GenAlloc

FileParser.o: FileParser.cpp FileParser.h Members.h
	$(CXX) $(CXXFLAGS) -c FileParser.cpp -o FileParser.o

Allocation.o: Allocation.cpp Allocation.h Members.h
	$(CXX) $(CXXFLAGS) -c Allocation.cpp -o Allocation.o

clean:
	rm -f *~ *.o *.stackdump GenAlloc