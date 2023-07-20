/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollarsignexpansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:36:09 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/17 15:50:53 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	dollarsignexpansion(char *str, t_data *data)
{
	t_env_list	*current;
	char		*word;
	int			m;

	m = 0;
	word = malloc(1000);
	if (word == NULL)
	{
		printf("malloc error");
		exit (EXIT_FAILURE);
	}
	(data->i)++;
	while (character(str[data->i]) == 1)
	{
		word[m] = str[data->i];
		(data->i)++;
		m++;
	}
	word[m] = 0;
	if (searchlist(data->env_sorted, word) != NULL)
	{
		current = searchlist(data->env_sorted, word);
		ft_strlcpy(word, current->value, 1000);
		m = 0;
		while (word[m] != 0)
		{
			data->lexer_output[data->k][data->j] = word[m];
			m++;
			data->j += 1;
		}
	}
	free(word);
}
