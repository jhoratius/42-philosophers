# Colors
GREEN = \033[0;32m
RESET = \033[0m

NAME =		philo

CC 			= cc
CFLAGS 		= -Wall -Wextra -Werror -g3
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
	@$(CC) $(CFLAGS) $(DFLAGS) -pthread -Iincludes -o $(NAME) $(OBJS)
	@echo "Done compiling."

$(OBJDIR)%.o: %.c includes/philosophers.h
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) $(DFLAGS) -Iincludes -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@$(RM) -r $(OBJDIR)
	@echo "Cleaned files."

fclean: clean
	@$(RM) $(NAME)
	@echo "Cleaned executable."

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re



# ------------------------------------------------------------------------------------------------------------- >
#
# 				████████╗███████╗░██████╗████████╗███████╗██╗░░░██╗██████╗░
# 				╚══██╔══╝██╔════╝██╔════╝╚══██╔══╝██╔════╝██║░░░██║██╔══██╗
# 				░░░██║░░░█████╗░░╚█████╗░░░░██║░░░█████╗░░██║░░░██║██████╔╝
# 				░░░██║░░░██╔══╝░░░╚═══██╗░░░██║░░░██╔══╝░░██║░░░██║██╔══██╗
# 				░░░██║░░░███████╗██████╔╝░░░██║░░░███████╗╚██████╔╝██║░░██║
# 				░░░╚═╝░░░╚══════╝╚═════╝░░░░╚═╝░░░╚══════╝░╚═════╝░╚═╝░░╚═╝

# 		COPY PASTE ALL OF THIS SOMEWHERE IN YOUR MAKEFILE

# 	MAKE SURE THE NAME OF THE PROJECT IS:
# 		$(NAME) = philo
# 		$(NAME_BONUS) = philo_bonus
# 	or else change the values below

# 	AVAILABLE: (see desccription below)
# 	make a
# 	make m
# 	make n

# NAMEE = philo
# NAMEE_BONUS = philo_bonus

# NUM_PHILO = 5
# TIME_DIE = 605
# TIME_EAT = 300
# TIME_SLEEP = 300

# ARGZ = $(NUM_PHILO) $(TIME_DIE) $(TIME_EAT) $(TIME_SLEEP) 3

# # MAKE A: Run with argz
# #
# a: $(NAMEE)
# 	@$(call random_shmol_cat, "\'tis $(NAMEE): $(ARGZ)", 死ぬかな..., $(CLS), );
# 	./$(word 1, $^) $(ARGZ)


# # MAKE N: Run a dozen bad arguments, with valgrind
# #
# n: $(NAMEE)
# 	@for arg in $(BAD_ARGS); do \
# 	$(call random_shmol_cat, teshting lots of bad args:, $$arg, $(CLS), ); \
# 	$(HELLGRIND) ./$(word 1, $^) $$arg; \
# 	echo "\t\033[5m~ Press Enter to continue...\033[0m"; read -p "" key; \
# 	done
# 	@$(call random_shmol_cat, this one is for valgriind output only:, valgrind doesnt like philosophers、some will die, $(CLS), )
# 	$(VALGRIIND) ./$(word 1, $^) 3 500 100 200 2

# BAD_ARGS = "3 5 1 1 2a" \
# 			"3 5 1 wtf" \
# 			"3 5 1 -2147483650" \
# 			"3 5 1 2147483646 2147483647" \
# 			"3 5 1 9999999999 9" \
# 			"4 3 2" \
# 			"4 3 2 1 1 1" \
# 			"" \
# 			"4 3 2 00000000000000 -" \
# 			"i want ... youuu" \
# 			"5 1-2 4 5"


# # MAKE M: Run life threatening arguments (no valgrind, make things fucked up)
# # -@$(call helper_tester, $(ARG_SET_1), "\'teshting the limits of the food chain:", shouldnt work, $(HELLGRIND))
# #
# m: $(NAMEE)
# 	-@$(call helper_tester, $(ARG_SET_2), "\'teshting the limits of the food chain:", should die without sleep, timeout 3s $(HELLGRIND))
# 	-@$(call helper_tester, $(ARG_SET_22), "\'teshting the limits of the food chain:", one should die, timeout 3s $(HELLGRIND))
# 	-@$(call helper_tester, $(ARG_SET_4), "\'teshting the limits of the food chain:", should all live happily ever after, )
# 	-@$(call helper_tester, $(ARG_SET_3), "\'teshting the limits of the food chain: MANY MIANY PHILO", should all live happily ever after, )
# 	-@$(call helper_tester, $(ARG_SET_5), "\'teshting the limits of the food chain:", one should die, )
# 	-@$(call helper_tester, $(ARG_SET_6), "\'teshting the limits of the food chain:", should all live happily ever after, )
# 	-@$(call helper_tester, $(ARG_SET_7), "\'teshting the limits of the food chain:", live or die? maybe?, )
# 	-@$(call helper_tester, $(ARG_SET_8), "\'teshting the limits of the food chain:", should stop after the first death in their sleep, timeout 3s $(HELLGRIND))
# 	-@$(call helper_tester, $(ARG_SET_9), "\'teshting the limits of the food chain:", should stop after the first death while eating, timeout 3s $(HELLGRIND))
# 	-@$(call helper_tester, $(ARG_SET_10), "\'teshting the limits of the food chain: SMALL TIMES", are you fast enough?, timeout 3s)
# 	-@$(call helper_tester, $(ARG_SET_11), "\'teshting the limits of the food chain: SMALL TIMES", are you fast enough?, timeout 3s)
# 	-@$(call helper_tester, $(ARG_SET_12), "\'teshting the limits of the food chain: SMALL TIMES", are you fast enough?, )
# 	-@$(call helper_tester, $(ARG_SET_13), "\'teshting the limits of the food chain: SMALL TIMES", are you fast enough?, )
# 	-@$(call random_shmol_cat, "\'teshting the limits of the food chain: MANY MIANY PHILO", $(ARG_SET_15), $(CLS), )
# 	@echo -e "\n\tTHIS ONE WILL TAKE A LOTS OF TIME\n\tgrep return 1 if no match found\n";
# 	-./$(word 1, $^) $(ARG_SET_15) | grep died
# 	@echo -e "\n\t\033[5m~ Press Enter to continue...\033[0m"; read -p "" key;
# 	-@$(call helper_tester, $(ARG_SET_14), "\'teshting the limits of the food chain:", They all should be HAPPY、and enjoy their last moment before the end..., timeout 10s $(HELLGRIND))
# 	@$(call random_shmol_cat, \033[5m(DISCLAIMER)\033[25m, No philosophers was harmed in the making of this test, $(CLS), );


# ARG_SET_1 = 0 60 60 60
# ARG_SET_2 = 1 1000 60 60
# ARG_SET_22 = 2 500 300 60
# ARG_SET_4 = 6 200 99 99 5
# ARG_SET_3 = 200 250 50 70 2
# ARG_SET_5 = 7 200 99 99 5
# ARG_SET_6 = 7 210 70 139 5
# ARG_SET_7 = 7 210 70 140 5
# ARG_SET_8 = 7 100 10 300
# ARG_SET_9 = 7 100 300 10
# ARG_SET_10 = 6 100 49 49
# ARG_SET_11 = 5 100 33 66
# ARG_SET_12 = 8 15 5 5 10
# ARG_SET_13 = 3 4 1 1 5
# ARG_SET_14 = 7 250 50 150
# ARG_SET_15 = 200 800 200 200 200

# # ------------------------------------------------------------------------------------------------------------- >
# # $(1)=$(ARGS) $(2)=$(TXT_cat) $(3)=$(TXT_below) $(4)=$(VALGRIND)(timeout 15s)
# define helper_tester
# 	$(call random_shmol_cat, $(2), $(1), $(CLS), )
# 	echo -e "\n\t$(3)\n"
# 	read -p "" key;
# 	$(4) ./$(word 1, $^) $(1)
# 	echo "\n\t\033[5m~ Press Enter to continue...\033[0m"; read -p "" key;
# endef

# # @$(call random_shmol_cat, text 1, text 2, $(CLS), $(RESET));
# # $(1)= $(CLEAR); $(2)= text1; $(3)= text2; $(4)= $(RESET)
# define random_shmol_cat
# 	COLOR=$$(printf "\033[38;5;%dm" $$(shuf -i 1-255 -n 1)); \
# 	COLOR2=$$(printf "\033[38;5;%dm" $$(shuf -i 1-255 -n 1)); \
# 	echo -e "$(3)$${COLOR2}\
# 	\tにゃ~$${COLOR}\t⠀╱|、\n\
# 	\t\t(˚ˎ。7⠀⠀⠀$${COLOR2}~ $(1) ~$${COLOR}\n\
# 	\t\t⠀|、˜\\\\\t\t$${COLOR2}~ $(2)$${COLOR}\n\
# 	\t\t⠀じしˍ)ノ\n$(4)"
# endef

# CLS = \033[2J\033[H
# # - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - -  - VALGRIIND
# VALGRIIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s --trace-children=yes --track-fds=yes
# HELLGRIND = valgrind --tool=helgrind
# # ------------------------------------------------------------------------------------------------------------- >
