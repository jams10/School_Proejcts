TARGET = c_news

WDIR = .

CC = gcc

CFLAGS = -Wall -O3 -D_REENTRANT
CFLAGS += -I${WDIR}/include

LDIR = -L./lib
LIBS = $(LDIR) -lfunclib

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

#=====================================
all : ${TARGET} clean
#=====================================
c_news : $(SRCS)
	$(CC) -static $(CFLAGS) -o $@ $? $(LIBS) -lpthread
#-------------------------------------
clean :
	rm -f core *.o a.out
#=====================================
