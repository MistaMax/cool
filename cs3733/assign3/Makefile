CFLAGS = gcc -g
OBJ = assign3p1.o assign3p2.o assign3p3.o pagetable.o phypages.o

all: assign3p1 assign3p2 assign3p3
# Automatic substitution using suffix rules to
# make .o files from either .c or .cpp files
%.o: %.c
	${CFLAGS} -c $< 

# Build xdir based on the required .o files

assign3p1: assign3p1.o
	${CFLAGS} -o assign3p1 assign3p1.o

assign3p2: assign3p2.o pagetable.o phypages.o
	${CFLAGS} -o assign3p2 assign3p2.o pagetable.o phypages.o

assign3p3: assign3p3.o pagetable.o phypages.o
	${CFLAGS} -o assign3p3 assign3p3.o pagetable.o phypages.o -lm

clean:
	rm ${OBJ}
