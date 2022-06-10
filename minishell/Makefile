NAME			=	minishell

FILES			=	main.c 			free_env.c		split.c			utils.c			\
					main_utils.c	env.c			ft_itoa.c		utils_lst.c		\
					ft_atoi.c		env_2.c			free_cmd.c		utils_str.c		\
					fd_mem.c														\
						builtins/builtins.c 		builtins/cd.c					\
						builtins/unset.c			builtins/echo.c					\
						builtins/pwd.c				builtins/export.c				\
						builtins/env.c				builtins/exit.c					\
						builtins/builtin_utils.c	builtins/export_utils.c			\
																					\
						parse_main.c				parse_utils_cmd_token.c			\
						parse_utils_token.c			parse_utils_cmd_list.c			\
																					\
					lex_main.c				lex_general.c		lex_utils.c			\
					lex_finisher_main.c 	lex_finisher.c		lex_check_token.c	\
																					\
					exec_star.c				exec_cmd_list.c		exec_apply_1.c		\
					exec_star_find_file.c	exec_cmd.c			exec_apply_2.c		\
					exec_cmd_token_list.c	exec_cmd_utils.c	exec_utils.c		\
					exec_cmd_list_check.c	ft_link.c			exec_utils_2.c

SRC_PATH		=	./srcs/
SRC				=	$(addprefix $(SRC_PATH), $(FILES))
OBJ				=	$(SRC:.c=.o)
DEP				=	$(SRC:.c=.d)
INCLUDE			=	./includes
INCLUDE_SYS		=	/usr/local/Cellar/readline/8.1.1/include
INCLUDE_SYS_S	=	/usr/local/Cellar/readline/8.1.1/include/readline
LIB_SYS			=	/usr/local/opt/readline/lib

CC				=	clang
CFLAGS			=	-MMD -Wall -Werror -Wextra -pedantic

all				:	$(NAME)

bonus			:	all

$(NAME)			:	$(OBJ)
					$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lreadline -L $(LIB_SYS)

%.o				:	%.c
					$(CC) $(CFLAGS) -c $< -o $@ -I$(INCLUDE) -I$(INCLUDE_SYS)

clean			:
					rm -f $(OBJ) $(DEP)
fclean			:	clean
					rm -f $(NAME)
re				:	fclean all


-include $(DEP)

.PHONY			:	all clean fclean re
