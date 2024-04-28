##
## EPITECH PROJECT, 2022
## B-NWP-400-PAR-4-1-myftp-bilel.barkallah
## File description:
## Makefile
##

SRC	=	$(wildcard *.c)

OBJ	=	$(SRC:.c=.o)

NAME	=	myftp

all:
	gcc -c $(SRC) -g3
	gcc -o myftp *.c

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)
	rm -f *~

re:	fclean all