#	colors	#

BLACK=	$(shell tput -Txterm setaf 0)
RED= 	$(shell tput -Txterm setaf 1)
GREEN= 	$(shell tput -Txterm setaf 2)
WHITE= 	$(shell tput -Txterm setaf 7)
YELLOW=	$(shell tput -Txterm setaf 3)
BLUE=	$(shell tput -Txterm setaf 6)
END= 	$(shell tput -Txterm sgr0)

#			#

NAME = ../philo_bonus

CC = cc

FLAGS = -Wall -Wextra -Werror -O3

LIBS = philo.h

FILES =		monitoring.c\
			utils.c	\
			parse.c		\
			routine.c	\
			routine_utils.c	\
			init.c		\
			error.c		\
			checkers.c	\
			solo_philo.c \
			philo_monitor.c	\
			
OBJ_DIR = objs/

OBJ = $(FILES:.c=.o)

OBJ_PREFIXED = $(addprefix $(OBJ_DIR), $(OBJ))

all	: Makefile $(NAME)

$(NAME) : $(OBJ_PREFIXED)
		@$(CC) $(FLAGS) $(OBJ_PREFIXED) -o $(NAME)
#		@echo "$(GREEN)$(NAME) done ! ✅$(END)"

$(OBJ_DIR)%.o : %.c
		@mkdir -p $(OBJ_DIR)
		@echo "$(BLUE)Compiling: $^$(END)"
		@$(CC) $(FLAGS) -c $< -o $@
clean :
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)objects removed$(END)"

fclean : clean
	@rm -f $(NAME)
	@echo "$(RED)philo_bonus removed$(END)"
	@echo ""
	@echo "$(GREEN)cleaned ! ✅$(END)"
	@echo ""

re : fclean all

.PHONY: all re clean fclean