CFLAGS = $(shell pkg-config --cflags playerc++)
CFLAGS += $(shell pkg-config --cflags playercore)
CFLAGS += -I.


LIBS   = $(shell pkg-config --libs   playerc++)
LIBS   += $(shell pkg-config --libs  playerinterface)
LIBS   += $(shell pkg-config --libs  playercore)


all:
	echo $(CFLAGS)
	g++ $(CFLAGS) $(LIBS) -o lab7  lab7.cpp

