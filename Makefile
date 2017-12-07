PROGRAM = spinout.out 
CC      = gcc
CFLAGS  = -g -ansi -Wall -I/usr/X11R6/include -I/usr/pkg/include
LDFLAGS = -L/usr/X11R6/lib -L/usr/pkg/lib
LDLIBS  = -lglut -lGLU -lGL -lm

$(PROGRAM): 
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(PROGRAM) src/*.c $(LDLIBS)

.PHONY: beauty clean dist

beauty:
	-indent -nut -kr main.c
	-rm *~ *BAK

clean:
	-rm *.o $(PROGRAM) *core

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)
