CFLAGS = gcc -g
OBJ = pslibrary.o assign2.o

all: assign2
# Automatic substitution using suffix rules to
# make .o files from either .c or .cpp files
%.o: %.c
	${CFLAGS} -c $< 

# Build xdir based on the required .o files

assign2: pslibrary.o assign2.o
	${CFLAGS} -o assign2 assign2.o pslibrary.o
clean:
	rm ${OBJ}
