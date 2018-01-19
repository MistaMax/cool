CFLAGS = gcc -g
OBJ = myio.o driver1.o driver2.o

# Automatic substitution using suffix rules to
# make .o files from either .c or .cpp files
%.o: %.c
	${CFLAGS} -c $< 

# Build xdir based on the required .o files
driver1: myio.o driver1.o
	${CFLAGS} -o driver1 myio.o driver1.o

driver2: myio.o driver2.o
	${CFLAGS} -o driver2 myio.o driver2.o

clean:
	rm ${OBJ}
