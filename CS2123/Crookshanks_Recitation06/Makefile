# Makefile for programs in directory ch03-ex01-random-h 
# ***************************************************************

PROGRAMS =   rec06 \
    randtest 

# ***************************************************************
# Parameters to control Makefile operation
# Note that the gccx command script must be defined

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

random.o: random.c random.h
	$(CC) $(CFLAGS) -c random.c

randtest.o: randtest.c
	$(CC) $(CFLAGS) -c randtest.c

rec06.o: rec06.c random.h
	$(CC) $(CFLAGS) -c rec06.c

# ***************************************************************
# Executable programs

randtest: randtest.o
	$(CC) $(CFLAGS) -o randtest randtest.o

rec06: rec06.o random.o
	$(CC) $(CFLAGS) -o rec06  rec06.o random.o

