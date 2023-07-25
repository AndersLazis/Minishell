/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 00:00:58 by mschulme          #+#    #+#             */
/*   Updated: 2023/06/28 19:54:05 by aputiev          ###   ########.fr       */
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
#include <readline/readline.h>
#include <readline/history.h>
#include <limits.h>

int	pwd(void);
int	env(char **envp);


// typedef struct s_data
// {
//     t_env   *env;
// }   t_data;


// typedef struct s_env
// {
//     char            *value;
//     struct  s_env   *next;
    
// }   t_env;


#endif