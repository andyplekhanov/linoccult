TARGET	:= libloCalc.a
# loCalc.cc is not included here. It requires a special make target for mysql
SRCS	:= loAPSAstOrbSubModule.cc loAstOrbCalc.cc loAstOrbChebMaker.cc loAstOrbSubModule.cc loChebAstOrbSubModule.cc \
           loChebMakerSubModule.cc loChebSubModule.cc loModuleAstOrbCalc.cc loModuleCalc.cc loModuleChebAstOrbCalc.cc
OBJS	:= ${SRCS:.cc=.o}

CC = g++
CCFLAGS = -g -O2 -Wall -I../APSLib -I../loData -I../loAppl -I../APSMathLib -I../APSAstroData -I../APSAstroAlg -I../kdtree/include/CGLA -I../kdtree/include -I../kdtree/src/KDTree
LDFLAGS =
LIBS    = 

ifeq ($(MYSQL),1)
  mysqlflags = -DWITH_MYSQL
else
  mysqlflags=
endif

.PHONY: all clean distclean
all:: ${TARGET}

${TARGET}: ${OBJS} loCalc.o
	ar rcs $@ ${OBJS} loCalc.o

${OBJS}: %.o: %.cc
	${CC} ${CCFLAGS} -o $@ -c $< ${LIBS}

loCalc.o: loCalc.cc
	${CC} ${CCFLAGS} ${mysqlflags} -o $@ -c $< ${LIBS}

clean::
	-rm -f *~ *.o ${TARGET}

distclean:: clean

