CFLAGS = gcc -g
OBJ = recC1.o myio.o

# Automatic substitution using suffix rules to
# make .o files from either .c or .cpp files
%.o: %.c
	${CFLAGS} -c $< 

# Build xdir based on the required .o files
recC1: recC1.o myio.o
	${CFLAGS} -o recC1 recC1.o myio.o

clean:
	rm ${OBJ}
