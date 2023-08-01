/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollarsignexpansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:36:09 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/28 18:56:08 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	dollarsignexpansion(char *str, t_data *data)
{
	char		*str_exitcode;
	t_env_list	*current;
	char		*word;
	int			m;

	str_exitcode = NULL;
	word = ft_calloc(1000, 1);
	if (word == NULL)
	{
		printf("malloc error");
		exit (EXIT_FAILURE);
	}
	data->i += 1;
	m = 0;
	while (character(str[data->i]) == 1 && str[data->i] != '/')
	{
		word[m] = str[data->i];
		data->i += 1;
		m++;
	}
	current = searchlist(data->env_sorted, word);
	if (current != NULL)
	{
		ft_strlcpy(word, current->value, 1000);
		m = 0;
		while (word[m] != 0)
		{
			data->lexer_output[data->k][data->j] = word[m];
			data->j += 1;
			m++;
		}
	}
	else if (word[0] == '?' && word[1] == 0)
	{
		m = 0;
		str_exitcode = ft_itoa(data->exit_code);
		while (str_exitcode[m] != 0)
		{
			data->lexer_output[data->k][data->j] = str_exitcode[m];
			data->j += 1;
			m++;
		}
	}
	if (current == NULL && data->j == 0)
		data->helper_dollar = -1;
	free(str_exitcode);
	free(word);
}
