# Makefile for programs in directory 10-Linear-Structures
# ***************************************************************

PROGRAMS = \
    HW6

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

graph.o: graph.c queue.h
	$(CC) $(CFLAGS) -c graph.c

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c



# ***************************************************************
# Executable programs



HW6: graph.o queue.o
	$(CC) $(CFLAGS) -o HW6 graph.o queue.o ../booklib/cslib.a

