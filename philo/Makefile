NAME	= philo
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -pthread -g

SRC =	main.c \
		error.c \
		check_params.c \
		parser.c \
		init.c \
		utils.c \
		utils_check.c


OBJTS	= $(SRC:.c=.o)
OBJ		= $(addprefix ./obj/, $(OBJTS))
OBJ_DIR	= ./obj

RM		= rm -rf

VPATH	= includes

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
		$(RM) $(OBJ_TESTS)


fclean:	clean
		$(RM) $(NAME)
		$(RM) obj/

re:		fclean all

val:
	valgrind --suppressions=readline.supp -s --show-leak-kinds=all --leak-check=full --track-fds=yes ./minishell

gdb:	obj_dir $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -o a.out

.PHONY= all clean fclean re $(NAME)