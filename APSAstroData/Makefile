TARGET	:= libAPSAstroData.a
SRCS	:= apsetutdata.cc apsjpleph.cc apsmoduleetutdata.cc apsmoduletaiutcdata.cc apstaiutcdata.cc
OBJS	:= ${SRCS:.cc=.o}

CC = g++
CCFLAGS = -g -O2 -Wall -IAPSLib -IAPSMathLib
LDFLAGS =
LIBS    = 

.PHONY: all clean distclean
all:: ${TARGET}

${TARGET}: ${OBJS} jpleph.o
	ar rcs $@ ${OBJS} jpleph.o

${OBJS}: %.o: %.cc
	${CC} ${CCFLAGS} -o $@ -c $< ${LIBS}

jpleph.o: jpleph.cc
	${CC}  -Wall -c jpleph.cc

clean::
	-rm -f *~ *.o ${TARGET}

distclean:: clean

