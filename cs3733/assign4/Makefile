CFLAGS = gcc -g
OBJ = assign4p1.o assign4p2.o assign4p3.o assign4p4.o philosopher.o
LIBTHREAD = -lpthread

all: assign4p1 assign4p2 assign4p3 assign4p4
# Automatic substitution using suffix rules to
# make .o files from either .c or .cpp files
%.o: %.c
	${CFLAGS} -c $< 

# Build xdir based on the required .o files

assign4p1: assign4p1.o philosopher.o
	${CFLAGS} -o assign4p1 assign4p1.o philosopher.o $(LIBTHREAD)

assign4p2: assign4p2.o philosopher.o
	${CFLAGS} -o assign4p2 assign4p2.o philosopher.o $(LIBTHREAD)

assign4p3: assign4p3.o philosopher.o
	${CFLAGS} -o assign4p3 assign4p3.o philosopher.o $(LIBTHREAD)

assign4p4: assign4p4.o philosopher.o
	${CFLAGS} -o assign4p4 assign4p4.o philosopher.o $(LIBTHREAD)

clean:
	rm ${OBJ}