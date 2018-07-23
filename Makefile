PROGRAM=l2fwd_Rawsocket
OBJS=main.o ether.o queue.o packetAnalyze.o
SRCS=main.c ether.c queue.c packetAnalyze.c

CFLAGS=-Wall -g
LFLAGS=-pthread
CC=gcc

all:$(PROGRAM)
$(PROGRAM):$(OBJS)
	$(CC) -o $(PROGRAM) $(OBJS) $(LFLAGS)
$(OBJS):$(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)

clean:
	$(RM) $(PROGRAM) $(OBJS)
