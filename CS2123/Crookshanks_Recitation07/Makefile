# Makefile for programs in directory 08-Abstract-Data-Types
# ***************************************************************

PROGRAMS = \
    rpncalc \
    testscan

# ***************************************************************
# Parameters to control Makefile operation
# Note that the gccx command script must be defined

#CC = gccx
#gcc -I..booklib  -o prog   prog.c  ../booklib/cslib.a
CC = gcc
CFLAGS = 

# ***************************************************************
# Entry to bring the package up to date

all: $(PROGRAMS)

# ***************************************************************
# Standard entries to remove files from the directories
#    tidy    -- eliminate unwanted files
#    scratch -- delete derived files in preparation for rebuild

tidy:
	rm -f ,* .,* *~ core a.out graphics.ps

scratch: tidy
	rm -f *.o *.a $(PROGRAMS)

# ***************************************************************
# C compilations

rpncalc.o: rpncalc.c stack.h strlib.h simpio.h genlib.h
	$(CC) $(CFLAGS) -c rpncalc.c

scanadt.o: scanadt.c scanadt.h genlib.h
	$(CC) $(CFLAGS) -c scanadt.c

exception.o: exception.c exception.h
	$(CC) $(CFLAGS) -c exception.c

genlib.o: genlib.c gcalloc.h exception.h
	$(CC) $(CFLAGS) -c genlib.c

strlib.o: strlib.c strlib.h genlib.h
	$(CC) $(CFLAGS) -c strlib.c

simpio.o: simpio.c simpio.h genlib.h strlib.h
	$(CC) $(CFLAGS) -c simpio.c

stack.o: stack.c stack.h genlib.h
	$(CC) $(CFLAGS) -c stack.c

testscan.o: testscan.c scanadt.h
	$(CC) $(CFLAGS) -c testscan.c


# ***************************************************************
# Executable programs

rpncalc: rpncalc.o stack.o
	$(CC) $(CFLAGS) -o rpncalc rpncalc.o stack.o

testscan: testscan.o scanadt.o
	$(CC) $(CFLAGS) -o testscan testscan.o scanadt.o
