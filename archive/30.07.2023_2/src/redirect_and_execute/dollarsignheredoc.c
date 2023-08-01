/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollarsignheredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:36:09 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/29 23:47:43 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	help_ques(t_data *data, char *excode, char *new_str);
static void	help_doll(t_data *data, char *excode, char *new_str);
static void	help_subs(t_data *data, char *old_str, char *new_str, char *word, char *excode);

void	dollarsignheredoc(char *old_str, t_data *data, char *new_str)
{
	char	*str_exitcode;
	char	*word;

	str_exitcode = NULL;
	word = ft_calloc(1000, 1);
	if (word == NULL)
		exit (EXIT_FAILURE);
	if (space(old_str[data->i + 1]) == 1 || old_str[data->i + 1] == '\"' || old_str[data->i + 1] == '\'' || old_str[data->i + 1] == 0)
	{
		new_str[data->j] = '$';
		data->i += 1;
		data->j += 1;
	}
	else if (old_str[data->i + 1] == '?')
		help_ques(data, str_exitcode, new_str);
	else if (old_str[data->i + 1] == '$')
		help_doll(data, str_exitcode, new_str);
	else
		help_subs(data, old_str, new_str, word, str_exitcode);
	free (word); 
}

static void	help_ques(t_data *data, char *excode, char *new_str)
{
	int	m;

	m = 0;
	excode = ft_itoa(data->exit_code);
	while (excode[m] != 0)
	{
		new_str[data->j] = excode[m];
		data->j += 1;
		m++;
	}
	data->i += 2;
	free(excode);
}

static void	help_doll(t_data *data, char *excode, char *new_str)
{
	int	m;

	m = 0;
	excode = ft_itoa(69420);
	while (excode[m] != 0)
	{
		new_str[data->j] = excode[m];
		data->j += 1;
		m++;
	}
	data->i += 2;
	free(excode);
}

static void	help_subs(t_data *data, char *old_str, char *new_str, char *word, char *excode)
{
	t_env_list	*current;
	int			m;

	m = 0;
	data->i += 1;
	while (character(old_str[data->i]) == 1)
	{
		word[m++] = old_str[data->i];
		data->i += 1;
	}
	current = searchlist(data->env_sorted, word);
	if (current != NULL)
	{
		ft_strlcpy(word, current->value, ft_strlen(current->value) +1);
		m = 0;
		while (word[m] != 0)
		{
			new_str[data->j] = word[m++];
			data->j += 1;
		}
	}
	free(excode);
}
