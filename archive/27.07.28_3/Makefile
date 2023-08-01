# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/23 18:27:07 by mschulme          #+#    #+#              #
#    Updated: 2023/07/28 21:18:47 by mschulme         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = CC

CCFLAG = -Wall -Werror -Wextra -g

SRCS	=	minishell.c signal_handling.c reset_function.c \
			list_utils.c util_functions.c init_env.c oldpwd_shlvl.c \
			fsm/lexer.c fsm/fsm_character.c fsm/fsm_dollar.c fsm/fsm_double_quotes.c fsm/fsm_single_quotes.c \
			fsm/fsm_pipe.c fsm/fsm_smaller.c fsm/fsm_greater.c fsm/fsm_space.c fsm/dollarsignexpansion.c \
			syntax_checker.c find_path.c ft_split_arguments.c split_into_commands.c \
			built_in/ft_exit.c built_in/ft_env.c \
			built_in/ft_cd.c built_in/ft_pwd.c built_in/ft_echo.c \
			built_in/ft_export.c built_in/utils_export.c built_in/ft_unset.c \
			redirect_and_execute/redirect_in.c redirect_and_execute/redirect_out.c \
			redirect_and_execute/execute_no_pipe.c redirect_and_execute/execute_with_pipes.c \
			redirect_and_execute/execute_heredoc.c redirect_and_execute/redirect_utils.c

D_SRCS = ./src/
SRC = $(addprefix $(D_SRCS), $(SRCS))

D_LIB = ./libs/libft/
LIB = $(D_LIB)libft.a

OBJ = $(SRC:.c=.o)

all : $(NAME)

%.o:%.c
	@$(CC) $(CCFLAG) -I $(HOME)/goinfre/.brew/opt/readline/include/ -o $@ -c $<

$(NAME): $(OBJ) $(LIB)
	@$(CC) $(CCFLAG) $(OBJ) $(LIB) -L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline -o $(NAME)
	mkdir tmp
	echo Done!

$(LIB):
	@make -C $(D_LIB)

clean:
	@make clean -C $(D_LIB)
	@rm -f $(OBJ)
	@rm -rf tmp

fclean:
	@rm -f $(OBJ)
	@rm -f $(NAME)
	@rm -rf tmp
	@make fclean -C $(D_LIB)

.SILENT:

re : fclean all

.PHONY: all clean fclean re
