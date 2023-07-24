/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollarsignexpansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:36:09 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/24 12:17:27 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int convert_exit_code(t_data *data)	//<-Changed_23.07.24
{	
	if(WIFEXITED(data->exit_code))
		return(WEXITSTATUS(data->exit_code));
	else
		exit (EXIT_FAILURE);
}

void	dollarsignexpansion(char *str, t_data *data)
{
	t_env_list	*current;
	char		*word;
	int			m;

	word = ft_calloc(1000, 1);
	if (word == NULL)
	{
		printf("malloc error");
		exit (EXIT_FAILURE);
	}
	data->i += 1;
	m = 0;
	while (character(str[data->i]) == 1)
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
		
		int exit_status = convert_exit_code(data);	//<-Changed_23.07.24
		char *str = ft_itoa(exit_status);	//<-Changed_23.07.24
		while (str[m] != 0)
		{
			data->lexer_output[data->k][data->j] = str[m];
			data->j += 1;
			m++;
		}
	}
	
	if (current == NULL && data->j == 0)
		data->helper_dollar = -1;
	free(word);
}
