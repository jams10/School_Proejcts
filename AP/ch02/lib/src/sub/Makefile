TARGET = libop2lib.a libop2lib.so

CC = gcc

WDIR = ../../..
LDIR = ${WDIR}/lib

SHARED = -shared -fPIC

CFLAGS = -Wall -O3 -D_REENTRANT
CFLAGS += -I./include -I${WDIR}/include

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

#======================================
all : ${TARGET} clean
#======================================
libop2lib.a : $(OBJS)
	ar -rscv $@ $?
	mv $@ ${LDIR}

libop2lib.so : ${SRCS}
	$(CC) ${SHARED} $(CFLAGS) -o $@ $? $(LIBS)
	mv $@ ${LDIR}
#--------------------------------------
clean :
	rm -rf core *.o a.out
#======================================
