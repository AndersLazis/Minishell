/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 00:00:58 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/07 16:41:25 by aputiev          ###   ########.fr       */
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

typedef struct s_env_sorted
{
	char				*name;
	char				*value;
	struct s_env_sorted	*next;
}	t_env_sorted;

typedef struct s_env_unsorted
{
	char					*name;
	char					*value;
	struct s_env_unsorted	*next;
}	t_env_unsorted;

typedef struct s_data
{
	t_env_unsorted	*env_unsorted;
	t_env_sorted	*env_sorted;
	int				ac;
	char			**av;
	char			**envp;
	
}	t_data;

/* builtins.c */

int		pwd(void);

int		ft_env(t_data *data);

// int		ft_export(t_data *data);
int	ft_export(char *args,t_data *data);

int		init_env_unsorted(t_data *data, char **env);

int		init_env_sorted(t_data *data, char **env);

/* find_path.c */

char	*find_path(char *cmd, char **envp);

/* lexer.c */

char	**lexer(char *str, char **lexer_output, t_data *data);

void	check_command(int num_args, char **args, t_data *data);

char	**expander(char **str, t_data *data);

char	*ft_strdup_name(char *s1); //<-added
char	*ft_strdup_value(char *s1); //<-added
void 	print_env(char **env);
int 	print_unsorted_list(t_data *data);
int 	print_sorted_list(t_data *data);
int		is_env_var_name_valid(char *args);
int		is_quotes_are_closed(char *args);
int		is_env_var_exist(char *args,t_data *data);
int		ft_unset(char *args,t_data *data);

#endif