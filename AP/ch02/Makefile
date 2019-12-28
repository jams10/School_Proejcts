TARGET = main_lib_so main_lib_a

WDIR = .

CC = gcc

CFLAGS = -Wall -O3 -D_REENTRANT
CFLAGS += -I${WDIR}/include

LDIR = -L./lib
LIBS = $(LDIR) -lop1lib -lop2lib

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

#=====================================
all : ${TARGET} clean
#=====================================
main_lib_so : $(SRCS)
	$(CC) $(CFLAGS) -o $@ $? $(LIBS)

main_lib_a : $(SRCS)
	$(CC) -static $(CFLAGS) -o $@ $? $(LIBS)
#-------------------------------------
clean : 
	rm -f core *.o a.out
#=====================================
