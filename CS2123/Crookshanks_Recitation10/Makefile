# Makefile for programs in directory 10-Linear-Structures
# ***************************************************************

PROGRAMS = \
    checkout \
    array-qtest \
    list-qtest \
    rpncalc

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

checkout.o: checkout.c queue.h
	$(CC) $(CFLAGS) -c checkout.c

dstack.o: dstack.c stack.c
	$(CC) $(CFLAGS) -c dstack.c

qarray.o: qarray.c queue.h
	$(CC) $(CFLAGS) -c qarray.c

qlist.o: qlist.c queue.h
	$(CC) $(CFLAGS) -c qlist.c

qtest.o: qtest.c queue.h scanadt.h
	$(CC) $(CFLAGS) -c qtest.c

rpncalc.o: rpncalc.c stack.h
	$(CC) $(CFLAGS) -c rpncalc.c

scanadt.o: scanadt.c scanadt.h
	$(CC) $(CFLAGS) -c scanadt.c

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c


# ***************************************************************
# Executable programs

checkout: checkout.o qarray.o
	$(CC) $(CFLAGS) -o checkout checkout.o qarray.o  ../booklib/cslib.a

array-qtest: qtest.o scanadt.o qarray.o
	$(CC) $(CFLAGS) -o array-qtest qtest.o scanadt.o qarray.o  ../booklib/cslib.a

list-qtest: qtest.o scanadt.o qlist.o
	$(CC) $(CFLAGS) -o list-qtest qtest.o scanadt.o qlist.o  ../booklib/cslib.a

rpncalc: rpncalc.o stack.o
	$(CC) $(CFLAGS) -o rpncalc rpncalc.o stack.o  ../booklib/cslib.a

