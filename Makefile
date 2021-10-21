CC=gcc
CFLAGS = -ansi -Wall -Wextra -Werror -pedantic-errors
LIBS = -lm
SRCS= group.c spmat.c modularity.c MatrixShifting.c division.c PowerIteration.c algorithms.c cluster.c
OBJS= $(SRCS:.c=.o)
MAIN=cluster

all:    $(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

%.o: %.c
	$(CC) -c $(CFLAGS) $^ -o $@

clean:
	rm -f $(OBJS) $(MAIN)



