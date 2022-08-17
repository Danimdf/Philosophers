NAME	= philo
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -pthread -g -I includes/

SRC =	main.c \
		error.c \
		check_params.c \
		free_all.c \
		one_philo.c \
		parser.c \
		init.c \
		utils.c \
		utils_actions.c \
		utils_check.c \
		utils_data_race.c \
		utils_threads.c \
		philo_actions.c

OBJTS	= $(SRC:.c=.o)
OBJ		= $(addprefix ./obj/, $(OBJTS))
OBJ_DIR	= ./obj

RM		= rm -rf

VPATH	= includes utils

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all:		obj_dir $(NAME)

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

obj_dir:
			@mkdir -p $(OBJ_DIR)

$(LIBFT):
			make -C $(LIBFT_PATH)

clean:
		$(RM) $(OBJ)

fclean:	clean
		$(RM) $(NAME)
		$(RM) obj/

re:		fclean all

val:
	valgrind --suppressions=readline.supp -s --show-leak-kinds=all --leak-check=full --track-fds=yes ./minishell

gdb:	obj_dir $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -o a.out

.PHONY= all clean fclean re $(NAME)
