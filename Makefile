# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/23 18:27:07 by mschulme          #+#    #+#              #
#    Updated: 2023/08/03 20:12:03 by mschulme         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = CC

CCFLAG = -Wall -Werror -Wextra -g 

SRCS	=	minishell.c signal_handling.c reset_function.c split_args_utils.c exit_ctrl_d.c \
			list_utils.c util_functions.c utils_functions_2.c init_env.c oldpwd_shlvl.c \
			fsm/lexer.c fsm/fsm_character.c fsm/fsm_dollar.c fsm/fsm_double_quotes.c fsm/fsm_single_quotes.c \
			fsm/fsm_pipe.c fsm/fsm_smaller.c fsm/fsm_greater.c fsm/fsm_space.c fsm/dollarsignexpansion.c \
			syntax_checker.c syntax_checker_utils.c syntax_checker_utils_2.c \
			find_path.c split_args.c split_into_commands.c \
			built_in/ft_exit.c built_in/ft_exit_utils.c built_in/ft_env.c \
			built_in/ft_cd.c built_in/ft_cd_utils.c built_in/ft_pwd.c built_in/ft_echo.c \
			built_in/ft_export.c built_in/utils_export.c built_in/utils_export_2.c built_in/ft_unset.c \
			redirect_and_execute/redirect_out.c  redirect_and_execute/execute_no_pipe_helper.c\
			redirect_and_execute/execute_no_pipe.c redirect_and_execute/execute_with_pipes.c \
			redirect_and_execute/execute_heredoc.c redirect_and_execute/redirect_utils.c \
			redirect_and_execute/dollarsignheredoc.c redirect_and_execute/execute_heredoc_pipes.c \
			redirect_and_execute/clean_up_functions.c redirect_and_execute/redirect_and_execute_utils.c

D_SRCS = ./src/
SRC = $(addprefix $(D_SRCS), $(SRCS))

D_LIB = ./libs/libft/
LIB = $(D_LIB)libft.a

D_LIB_2 = ./libs/printf/
LIB_2 = $(D_LIB_2)libftprintf.a

OBJ = $(SRC:.c=.o)

all : $(NAME)

%.o:%.c
	@$(CC) $(CCFLAG) -I $(HOME)/goinfre/.brew/opt/readline/include/ -o $@ -c $<

$(NAME): $(OBJ) $(LIB) $(LIB_2)
	@$(CC) $(CCFLAG) $(OBJ) $(LIB) $(LIB_2) -L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline -o $(NAME)
	mkdir tmp
	echo Done!

$(LIB):
	@make -C $(D_LIB)

$(LIB_2):
	@make -C $(D_LIB_2)

clean:
	@make clean -C $(D_LIB)
	@make clean -C $(D_LIB_2)
	@rm -f $(OBJ)

fclean:
	@rm -f $(OBJ)
	@rm -f $(NAME)
	@rm -rf tmp
	@make fclean -C $(D_LIB)
	@make clean -C $(D_LIB_2)
		
.SILENT:

re : fclean all

.PHONY: all clean fclean re
