# Colors
GREEN = \033[0;32m
RESET = \033[0m

NAME =		philosophers

CC 			= cc
CFLAGS 		= -Wall -Wextra -Werror -g3
DFLAGS		= -MMD -MP
RM 			= rm -f
EXTS 	=	.c

MAIN	= src/
OBJDIR	= obj/

FILES		=	free				\
				main				\
				parsing 			\
				utils				\

PHILO_FILES	=	philosophes			\

SRCS_MAIN	= $(addsuffix ${EXTS}, src/$(FILES))
SCRS_PHILO	= $(addsuffix ${EXTS}, routine/$(PHILO_FILES))

SRCS = $(SRCS_MAIN) $(SCRS_PHILO)
OBJS	= $(addprefix $(OBJDIR), $(notdir $(SRCS:.c=.o)))
DEPS	= $(OBJS:.o=.d)

vpath %.c src routine

all: $(NAME)

$(NAME): $(OBJS) includes/philosophers.h
	@$(CC) $(CFLAGS) $(DFLAGS) -pthread -Iincludes -o $(NAME) $(OBJS)
	@echo "$(GREEN)Done compiling.$(RESET)$(NC)"

$(OBJDIR)%.o: %.c includes/philosophers.h
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) $(DFLAGS) -Iincludes -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@$(RM) -r $(OBJDIR)
	@echo "$(BLUE)Cleaned files.$(RESET)$(NC)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(BLUE)Cleaned executable.$(RESET)$(NC)"

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
