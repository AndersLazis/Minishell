/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 00:00:58 by mschulme          #+#    #+#             */
/*   Updated: 2023/08/01 20:44:38 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <limits.h>
# include <errno.h>
# include <termios.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libs/libft.h"
# include "../libs/ft_printf.h"

# define ERROR -1
# define CHILD 0
# define CURRENT 0
# define PREVIOUS 1
# define READ 0
# define WRITE 1
# define TRUNCATE 1
# define APPEND 2

# define TTY_IS_CHILD 0
# define TTY_HEREDOC 1
# define TTY_OMIT_LF 2

int	g_flags;

typedef struct s_env_list
{
	struct s_env_list	*next;
	char				*name;
	char				*value;
	int					equal_sign;
}	t_env_list;

typedef struct s_data
{
	t_env_list	*env_unsorted;
	t_env_list	*env_sorted;
	int			ac;
	char		**lexer_output;
	char		***command_array;
	char		**envp;
	char		**new_envp;
	char		**split;
	char		*command;
	char		**av;
	int			*heredoc_exists;
	int			m;
	int			i;
	int			j;
	int			k;
	int			index;
	pid_t		pid;
	int			pipe_count;
	int			pipes[1000][2];
	pid_t		pid_array[1000];
	int			error;
	bool		error_open_file;
	int			stop;
	int			nb_single_quotes;
	int			nb_double_quotes;
	int			helper_dollar;
	int			exit_code;
	char		*filename;
	int			save_in;
	int			save_out;
	int			heredoc_flag;
	char		*word;
	int			input;
	bool		cmd;
	int			mw_j;
}	t_data;

/* list_utils.c */

t_env_list	*sort_list(t_env_list *lst);
void		insert_at_end(t_env_list *head, char *name, char *value, int equal_sign);
void		create_old_pwd(t_env_list *head, char *old_pwd);
void		create_shlvl(t_env_list *head);
t_env_list	*swap_list_operation(t_env_list *lst, t_env_list *tmp);
/* util_functions.c */

void		increment_shell_level(t_data *data);
char		*trimwhitespace(char *str);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strdup_name(char *s1);
char		*ft_strdup_value(char *s1);
int			check_equal_sign(char *str);

/* init_env.c */

t_env_list	*deletenode(t_env_list *curr, char *name);
t_env_list	*searchlist(t_env_list *data, char *name);
void		init_env_sorted(t_data *data, char **env);
void		init_env_unsorted(t_data *data, char **env);

/* signal_handling.c */

void		signal_int_nothing(int signal);
void		signal_handler(int signal);
void		signal_handler_quit(int signal);

/* reset_funcion.c */

void		reset_function(char *command_line, t_data *data);

/* Finite state machine */

void		lexer(char *str, t_data *data);
int			space(char ch);
int			character(char ch);
void		fsm_space( char *str, t_data *data);
void		fsm_character(char *str, t_data *data);
void		fsm_pipe(char *str, t_data *data);
void		fsm_dollar(char *str, t_data *data);
void		dollarsignexpansion(char *str, t_data *data);
void		fsm_smaller(char *str, t_data *data);
void		fsm_greater(char *str, t_data *data);
void		fsm_double_quotes(char *str, t_data *data);
void		fsm_single_quotes(char *str, t_data *data);
void		fsm_backslash(char *str, t_data *data);

/* syntax_checker.c */

void		split_into_commands(t_data *data);
void		syntax_checker(t_data *data);

/* find_path.c */

char		*find_path(char *cmd, char **envp);

/* split_args.c */

char		**split_args(char *str, t_data *data);
char		*process_double_quote(char *str_save, char *str, t_data *data);
char		*process_single_quote(char *str_save, char *str, t_data *data);

/* Built_in */

int			ft_exit(t_data *data);
void		ft_env(t_data *data);
void		ft_cd(t_data *data);
void		ft_echo(t_data *data);
int			ft_pwd(void);
void		ft_unset(t_data *data);
int			remove_env_var_in_unsorted(char *name, t_data *data);
int			remove_env_var_in_sorted(char *name, t_data *data);
int			free_unsorted_list(t_data *data);
int			free_sorted_list(t_data *data);
int			print_oldpwd(t_data *data);
int			oldpwd_update(char *old_pwd_sorted, char *old_pwd_unsorted, t_data *data);
int			currentpwd_update(t_data *data);
void		print_echo(t_data	*data, int j, int flag_new_line);

/* ft_export and helper functions */

void		ft_export(t_data *data);
void		export_exist_variable(t_data *data, int i);
void		export_new_variable(t_data *data, int i);
int			update_envp(t_data *data);
int			is_env_var_name_valid(char **split, t_data *data, int print_flag);

void		execute_with_pipes(t_data *data);
void		execute_no_pipe(t_data *data);
int			execute_build_in(t_data *data);
void		execution(t_data *data);

/* execute_heredoc.c */

bool		next_heredoc(t_data *data);
void		execute_heredoc(t_data *data);
void		heredoc_pipes(t_data *data);

/* dollarsignheredoc.c */

char		*dollar_substitution(t_data *data, char *line);
void		dollarsignheredoc(char *old_str, t_data *data, char *new_str);

/* redirect_utils.c */

char		**my_realloc(void *ptr, size_t new_size);
char		**add_string(char **array, char *string);

/* redirect_out.c */

bool		redirect_out(t_data *data);

/* syntax_checker.c */

void		split_into_commands(t_data *data);
void		syntax_checker(t_data *data);
void		print_syntax_error_op_in_end(t_data *data);
void		print_syntax_error_double_redirect_sign(t_data *data, int i);
void		print_syntax_error_double_redirect_sign(t_data *data, int i);
void		print_syntax_error_wrong_redirect_token(t_data *data);
void		syntax_check_operator(t_data *data, int i);
void		print_syntax_error_wrong_redirect_token_rev(t_data *data);
void		print_syntax_error_double_pipe(t_data *data);
void		syntax_check_syntax_of_first_element(t_data *data);
void		check_last_element(t_data *data, int i);

#endif