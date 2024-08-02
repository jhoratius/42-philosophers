NAME =		philosophers

CC 			= cc
CFLAGS 		= -Wall -Wextra -g3
RM 			= rm -f
EXTS 	=	.c

MAIN	= src/

GNLPRE		= get_next_line/

FILES		=	free				\
				main				\
				parsing 			\
				utils				\

GNLFILES	=	get_next_line 		\
				get_next_line_utils \

SRCS	= $(addsuffix ${EXTS}, \
			$(addprefix ${MAIN}, $(FILES)) \
			)

OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -pthread -o $(NAME) $(OBJS) 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(NAME) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
