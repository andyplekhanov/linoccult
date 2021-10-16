CXXFLAGS = -I../../include/CGLA -I../../include
sources							= $(shell ls *.cpp)
objects							= $(sources:.cpp=.o)

all: ${objects}
	ar -cr ../../lib/libCGLA.a ${objects}
clean:
	rm -f *.o *~ 
