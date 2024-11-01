# Colors
GREEN = \033[0;32m
RESET = \033[0m

NAME =		philo

CC 			= cc
CFLAGS 		= -Wall -Wextra -Werror -g3 -o3
DFLAGS		= -MMD -MP
RM 			= rm -f
EXTS 	=	.c

MAIN	= src/
OBJDIR	= obj/

PHILO_FILES	=	philo_lunch			\
				philosophes			\

FILES		=	checks				\
				free				\
				init				\
				main				\
				parsing 			\
				safe_locks			\
				utils				\

SCRS_PHILO	= $(addsuffix ${EXTS}, routine/$(PHILO_FILES))
SRCS_MAIN	= $(addsuffix ${EXTS}, src/$(FILES))

SRCS = $(SRCS_MAIN) $(SCRS_PHILO)
OBJS	= $(addprefix $(OBJDIR), $(notdir $(SRCS:.c=.o)))
DEPS	= $(OBJS:.o=.d)

vpath %.c src routine

all: $(NAME)

$(NAME): $(OBJS) includes/philosophers.h
	$(CC) $(CFLAGS) $(DFLAGS) -pthread -Iincludes -o $(NAME) $(OBJS)
	@echo "Done compiling."

# a: $(NAME)
# 	clear
# 	./$(NAME) 200 800 200 200

# v: $(NAME)
# 	clear
# 	$(HELLGRIND) ./$(NAME) 200 600 200 200 

$(OBJDIR)%.o: %.c includes/philosophers.h
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(DFLAGS) -Iincludes -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(RM) -r $(OBJDIR)
	@echo "Cleaned files."

fclean: clean
	$(RM) $(NAME)
	@echo "Cleaned executable."

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
