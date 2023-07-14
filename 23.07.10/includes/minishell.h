/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 00:00:58 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/08 19:47:18 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "libft.h"

typedef struct s_env_list
{
	struct s_env_list*next;
	char				*name;
	char				*value;
}	t_env_list;

typedef struct s_data
{
	t_env_list	*env_unsorted;
	t_env_list	*env_sorted;
	
	int				ac;
	char			**lexer_output;
	char			**envp;
	char			**split;
	char			**av;
	int				i;
	int				j;
	int				k;
	int				error;
	int				nb_single_quotes;
	int				nb_double_quotes;
}	t_data;

/* list_utils.c */

t_env_list	*sort_list(t_env_list *lst);
void		insert_at_end(t_env_list *head, char *name, char *value);

/* util_functions.c */

int	ft_strcmp(char *s1, char *s2);
char	*ft_strdup_name(char *s1);
char	*ft_strdup_value(char *s1);

/* init_env.c */

t_env_list	*deletenode(t_env_list *curr, char *name);
t_env_list	*searchlist(t_env_list *data, char *name);
void		init_env_sorted(t_data *data, char **env);
void		init_env_unsorted(t_data *data, char **env);

/* signal_handling.c */

void	setup_signal_handling(void);

/* Finite state machine */

void	lexer(char *str, t_data *data);
int		character(char ch);
void	fsm_space( char *str, t_data *data);
void	fsm_character(char *str, t_data *data);
void	fsm_pipe(char *str, t_data *data);
void	fsm_dollar(char *str, t_data *data);
void	fsm_smaller(char *str, t_data *data);
void	fsm_greater(char *str, t_data *data);
void	fsm_double_quotes(char *str, t_data *data);
void	fsm_single_quotes(char *str, t_data *data);
void	fsm_backslash(char *str, t_data *data);
void	fsm_semicolon(char *str, t_data *data);

/* syntax_checker.c */

void	syntax_checker(t_data *data);

/* find_path.c */

char	*find_path(char *cmd, char **envp);

/* ft_split_arguments.c */

char	**ft_split_arguments(char *str, t_data *data);

/* Built_in */

void	ft_exit(t_data *data);
void	ft_env(t_data *data);
void	ft_cd(t_data *data);
void	ft_echo(t_data*data);
int		ft_pwd(t_data *data);
void	ft_unset(t_data *data);
/* ft_export and helper functions */

void	ft_export(t_data *data);
int		is_env_var_name_valid(t_data *data);

void	executor(t_data *data);


#endif