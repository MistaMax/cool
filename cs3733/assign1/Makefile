CFLAGS = gcc -g
OBJ = assign1-0.o pslibrary.o assign1.o

all: assign1 assign1-0
# Automatic substitution using suffix rules to
# make .o files from either .c or .cpp files
%.o: %.c
	${CFLAGS} -c $< 

# Build xdir based on the required .o files
assign1-0: assign1-0.o pslibrary.o
	${CFLAGS} -o assign1-0 assign1-0.o pslibrary.o

assign1: pslibrary.o assign1.o
	${CFLAGS} -o assign1 assign1.o pslibrary.o
clean:
	rm ${OBJ}
