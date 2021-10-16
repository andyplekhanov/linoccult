TARGET	:= libloIO.a
SRCS	:= $(shell ls *.cc)
OBJS	:= ${SRCS:.cc=.o}

CC = g++
CCFLAGS = -g -O2 -Wall -I../APSLib -I../APSMathLib -I../APSAstroIO -I../APSAstroAlg -I../loData -I../loAppl -I../loCalc -I../kdtree/include/CGLA -I../kdtree/include -I../kdtree/src/KDTree
LDFLAGS =
LIBS    = 

.PHONY: all clean distclean
all:: ${TARGET}

${TARGET}: ${OBJS}
	ar rcs $@ ${OBJS}

${OBJS}: %.o: %.cc
	${CC} ${CCFLAGS} -o $@ -c $< ${LIBS}


clean::
	-rm -f *~ *.o ${TARGET}

distclean:: clean

