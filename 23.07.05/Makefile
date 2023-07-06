NAME		= minishell
CC			= gcc
CFLAGS		= -L /goinfre/aputiev/.brew/opt/readline/lib -I /goinfre/aputiev/.brew/opt/readline/include -lreadline
RM			= /bin/rm -f
INCLUDE_DIR	= includes
LIBFT		= libft.a
INCLUDE		= -I include
BUILD_DIR	= build
SRC_DIR		= ./src
SRCS		=	minishell.c lexer.c init_env_unsorted.c \
				init_env_sorted.c find_path.c expander.c \
				builtins.c env.c export.c utils_export.c


				
OBJS =	$(SRCS:%.c=$(BUILD_DIR)/%.o)

all: $(NAME)
	./minishell

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) $(LIBFT) -o $(NAME)

$(OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) -g $(CFLAGS) $(INCLUDES) -c $< -o $@

re: fclean all

clean:
	$(RM) -r $(BUILD_DIR)

fclean: clean
	$(RM) $(NAME)
	
.PHONY:	all clean fclean re
