# pour linux
MESAHOME=/usr
X11HOME=/usr/X11R6

# pour solaris
#MESAHOME=/opt/net1/Mesa-3.0
#X11HOME=/usr/openwin

MESALIBS = -L$(MESAHOME)/lib -lglut -lMesaGLU -lMesaGL
XLIBS = -L$(X11HOME)/lib -lXmu -lXi -lXext -lX11

LIBS = $(MESALIBS) $(XLIBS) -lm

CPPFLAGS = -I$(MESAHOME)/include -I$(X11HOME)/include
CC = gcc
CFLAGS = -g -Wall

TARGETS = dino1 dino2 planet robot

all: $(TARGETS)

.SUFFIXES: .c

.c:
	$(CC) $(CFLAGS) $(CPPFLAGS) $< $(LIBS) -o $@
