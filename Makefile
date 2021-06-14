CC=gcc
SRC=parser.c learning.c main.c initialization.c liste.c -lm
OBJ=$(SRC:.c=.o)

iris:		$(OBJ)
	$(CC) $(OBJ) -o $@

%.o:	%.c
	$(CC) -c -Wall $< 
clean:
	rm *.o iris

