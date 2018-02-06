CFLAGS = gcc -g
OBJ = assign1-0.o pslibrary.o assign1.o

# Automatic substitution using suffix rules to
# make .o files from either .c or .cpp files
%.o: %.c
	${CFLAGS} -c $< 

# Build xdir based on the required .o files
a0: assign1-0.o pslibrary.o
	${CFLAGS} -o a0 assign1-0.o pslibrary.o

a1: pslibrary.o assign1.o
	${CFLAGS} -o a1 assign1.o pslibrary.o
clean:
	rm ${OBJ}
