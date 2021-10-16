TARGET	:= libloAppl.a
SRCS	:= $(shell ls *.cc)
OBJS	:= ${SRCS:.cc=.o}

CC = g++
CCFLAGS = -g -O2 -Wall -I../APSLib -I../APSMathLib -I../APSAstroAlg -I../APSAstroIO -I../loData -I../loIO -I../AstroIO -I../loCalc
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

