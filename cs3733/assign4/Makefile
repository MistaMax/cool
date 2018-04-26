CFLAGS = gcc -g
OBJ = assign4-part1.o assign4-part2.o assign4-part3.o assign4-part4.o
LIBTHREAD = -lpthread

all: assign4-part1 assign4-part2 assign4-part3 assign4-part4
# Automatic substitution using suffix rules to
# make .o files from either .c or .cpp files
%.o: %.c
	${CFLAGS} -c $< 

# Build xdir based on the required .o files

assign4-part1: assign4-part1.o 
	${CFLAGS} -o assign4-part1 assign4-part1.o  $(LIBTHREAD)

assign4-part2: assign4-part2.o 
	${CFLAGS} -o assign4-part2 assign4-part2.o  $(LIBTHREAD)

assign4-part3: assign4-part3.o 
	${CFLAGS} -o assign4-part3 assign4-part3.o  $(LIBTHREAD)

assign4-part4: assign4-part4.o 
	${CFLAGS} -o assign4-part4 assign4-part4.o  $(LIBTHREAD)

clean:
	rm ${OBJ}