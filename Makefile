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

PHILO_FILES	=	philosophes			\

GNLFILES	=	get_next_line 		\
				get_next_line_utils \

SRCS_MAIN	= $(addsuffix ${EXTS}, src/$(FILES))
SCRS_PHILO	= $(addsuffix ${EXTS}, routine/$(PHILO_FILES))

SRCS = $(SRCS_MAIN) $(SCRS_PHILO)

OBJS	= $(SRCS:.c=.o)

vpath %.c src routine

all: $(NAME)

$(NAME): $(OBJS) includes/philosophers.h
	$(CC) $(CFLAGS) -pthread -Iincludes -o $(NAME) $(OBJS) 

%.o: %.c includes/philosophers.h
	$(CC) $(CFLAGS) -Iincludes -c $< -o $@

clean:
	$(RM) $(NAME) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
