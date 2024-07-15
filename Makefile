NAME = philosophers

CC 			= cc
CFLAGS 		= -Wall -Wextra
RM 			= rm -f
EXTS 	=	.c

MAIN	= src/

GNLPRE		= get_next_line/

FILES	=	main				\
			parsing 			\

GNLFILES	=	get_next_line 		\
				get_next_line_utils \

SRCS	= $(addsuffix ${EXTS}, \
			$(addprefix ${MAIN}, $(FILES)) \
			)

OBJS	= $(SRCS:.c=.o)

MANDATORY_BUILT = .mandatory_built

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	touch $(MANDATORY_BUILT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(NAME) $(OBJS) $(MANDATORY_BUILT)

fclean: clean
	$(RM) $(NAME)

re: clean all

.PHONY: all clean fclean re
