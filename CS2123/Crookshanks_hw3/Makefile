# Makefile for programs in directory 08-Abstract-Data-Types
# ***************************************************************

PROGRAMS = \
	driver

# ***************************************************************
# Parameters to control Makefile operation
# Note that the gccx command script must be defined

#CC = gccx
#gcc -I..booklib  -o prog   prog.c  ../booklib/cslib.a
CC = gcc -I../booklib
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

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

genlib.o: genlib.c genlib.h
	$(CC) $(CFLAGS) -c genlib.c

exception.o: exception.c exception.h
	$(CC) $(CFLAGS) -c exception.c

driver.o: driver.c stack.h genlib.h exception.h
	$(CC) $(CFLAGS) -c driver.c

# ***************************************************************
# Executable programs

driver: driver.o stack.o genlib.o exception.o
	$(CC) $(CFLAGS) -o driver driver.o stack.o genlib.o exception.o
