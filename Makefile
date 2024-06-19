CC 			= gcc
CFLAGS 	= -O4 -Wall
OBJS 		= main.o mySHA256.o mySHA2gen.o
PROGRAM = mySHA2

all: 				$(PROGRAM)
$(PROGRAM): $(OBJS)
						$(CC) $(OBJS) -o $(PROGRAM)
clean:; 		rm -f *.o *~ $(PROGRAM)


