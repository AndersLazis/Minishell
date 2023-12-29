/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollarsignexpansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:36:09 by mschulme          #+#    #+#             */
/*   Updated: 2023/08/02 23:26:26 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	help_ques(t_data *data, char *word, char *str_exitcode);
void	help_doll(t_data *data, char *word, char *str_exitcode);
void	help_subs(char *str, t_data *data, char *word, char *excode);

void	dollarsignexpansion(char *str, t_data *data)
{
	char	*str_exitcode;
	char	*word;

	str_exitcode = NULL;
	data->i += 1;
	word = ft_calloc(1000, 1);
	if (word == NULL)
		exit (EXIT_FAILURE);
	if (space(str[data->i]) == 1 || str[data->i] == '"' || str[data->i] == 0)
	{
		data->lexer_output[data->k][data->j] = '$';
		data->j += 1;
		free(word);
	}
	else if (str[data->i] == '?')
		help_ques(data, word, str_exitcode);
	else if (str[data->i] == '$')
		help_doll(data, word, str_exitcode);
	else
		help_subs(str, data, word, str_exitcode);
}

void	help_ques(t_data *data, char *word, char *excode)
{
	int	m;

	m = 0;
	excode = ft_itoa(data->exit_code);
	while (excode[m] != 0)
	{
		data->lexer_output[data->k][data->j] = excode[m];
		data->j += 1;
		m++;
	}
	data->i += 1;
	free(excode);
	free(word);
}

void	help_doll(t_data *data, char *word, char *excode)
{
	int	m;

	m = 0;
	excode = ft_itoa(69420);
	while (excode[m] != 0)
	{
		data->lexer_output[data->k][data->j] = excode[m];
		data->j += 1;
		m++;
	}
	data->i += 1;
	free(excode);
	free(word);
}

void	help_subs(char *str, t_data *data, char *word, char *excode)
{
	t_env_list	*current;
	int			m;

	m = 0;
	while (ft_isalpha(str[data->i]) == 1)
	{
		word[m++] = str[data->i];
		data->i += 1;
	}
	current = searchlist(data->env_sorted, word);
	if (current != NULL)
	{
		ft_strlcpy(word, current->value, 1000);
		m = 0;
		while (word[m] != 0)
		{
			data->lexer_output[data->k][data->j] = word[m++];
			data->j += 1;
		}
	}
	if (current == NULL && data->j == 0)
		data->helper_dollar = -1;
	free(excode);
	free(word);
}
