.SUFFIXES : .c .o

CC = /usr/bin/gcc
CPP = /usr/bin/g++
CFLAGS = -g -c -Wall
LDFLAGS= -Wall -lm

SRC= minish.c

OBJ= $(addsuffix .o, $(basename $(SRC)))

TARGET= minish

all: $(TARGET)

minish: minish.o
	$(CC) $(LDFLAGS) $(LIBDIR) $(LIBFILE) -o $@ $^

.c.o:
	$(CC) $(CFLAGS) $(INCDIR) $<

clean:
	rm -rf $(OBJ) $(TARGET) core
