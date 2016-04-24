CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall -std=c++11 $(DEBUG)
OBJS = helpers.cpp kk.cpp

all: kk

kk : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o kk

clean:
	-rm kk