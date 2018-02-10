##
## EPITECH PROJECT, 2017
## lemin
## File description:
## makefile-graph
##

NAME	= visu_hex

CC	= gcc

RM	= rm -f

SRCS	= ./src/get_next_line.c \
	  ./src/graph.c \
	  ./src/itoa.c \
	  ./src/main.c \
	  ./src/maths.c \
	  ./src/parser.c \
	  ./src/pfmt.c \
	  ./src/printf.c \
	  ./src/utils.c 

OBJS	= $(SRCS:.c=.o)

CFLAGS = -I ./inc/
CFLAGS += -W -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(SRCS) $(CFLAGS) -lSDL2 -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
