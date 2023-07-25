NAME		= minishell
CC			= cc
RL_PREFIX	?= $(HOME)/.local/pkg/readline
CFLAGS		= -I $(RL_PREFIX)/include -L $(RL_PREFIX)/lib -l readline -l history -l curses 
RM			= /bin/rm -f
INCLUDE_DIR	= includes
LIBFT		= libft.a
INCLUDE		= -I include
BUILD_DIR	= build
SRC_DIR		= ./src
SRCS		=	minishell.c signal_handling.c \
				list_utils.c util_functions.c init_env.c \
				fsm/lexer.c fsm/fsm_character.c fsm/fsm_dollar.c fsm/fsm_double_quotes.c fsm/fsm_single_quotes.c \
				fsm/fsm_pipe.c fsm/fsm_smaller.c fsm/fsm_greater.c fsm/fsm_space.c fsm/dollarsignexpansion.c \
				syntax_checker.c find_path.c ft_split_arguments.c split_into_commands.c \
				built_in/ft_exit.c built_in/ft_env.c \
				built_in/ft_cd.c built_in/ft_pwd.c built_in/ft_echo.c \
				built_in/ft_export.c built_in/utils_export.c built_in/ft_unset.c \
				redirect_and_execute/redirect_and_execute.c redirect_and_execute/redirect_in.c redirect_and_execute/redirect_out.c redirect_and_execute/heredoc.c 

OBJS =	$(SRCS:%.c=$(BUILD_DIR)/%.o)

all: $(NAME)
	./minishell

$(NAME): $(OBJS)
	$(CC) -fsanitize=address $(CFLAGS) $(OBJS) $(INCLUDE) $(LIBFT) -o $(NAME)
	
$(OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) -g $(CFLAGS) $(INCLUDES) -c $< -o $@

re: fclean all

clean:
	$(RM) -r $(BUILD_DIR)

fclean: clean
	$(RM) $(NAME)
	
.PHONY:	all clean fclean re
