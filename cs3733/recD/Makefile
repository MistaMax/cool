CFLAGS = gcc -g
OBJ = myio.o bank.o customer.o

all: bank customer
# Automatic substitution using suffix rules to
# make .o files from either .c or .cpp files
%.o: %.c
	${CFLAGS} -c $< 

# Build xdir based on the required .o files
bank: bank.o
	${CFLAGS} -o bank bank.o

customer: myio.o customer.o
	${CFLAGS} -o customer customer.o myio.o

clean:
	rm ${OBJ}
