# in directory OPT123
# ***************************************************************

PROGRAMS =     wordsearch 

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

OPT123.o: OPT123.c
	$(CC) $(CFLAGS) -c OPT123.c


# ***************************************************************
# Executable programs
		
wordsearch: OPT123.o
	$(CC) $(CFLAGS) -o wordsearch OPT123.o