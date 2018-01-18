CFLAGS = gcc -g
OBJ = myio.o

# Automatic substitution using suffix rules to
# make .o files from either .c or .cpp files
%.o: %.c
	${CFLAGS} -c $< 

# Build xdir based on the required .o files
run: ${OBJ}
	${CFLAGS} -o run ${OBJ}

clean:
	rm ${OBJ}
