/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 23:54:16 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/27 18:18:36 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	next_heredoc(t_data *data)
{
	while (data->command_array[data->index][data->m] != NULL)
	{
		if (ft_strcmp(data->command_array[data->index][data->m], "<<") == 0)
		{
			data->m += 1;
			return (true);
		}
		data->m += 1;
	}
	return (false);
}

char	*dollar_substitution(t_data *data, char *line)	//<-changed_23.07.27
{
	char *var_name;
	char *new_str;
	int i;
	int k;
	t_env_list *current;
	//printf("line;%s\n", line);
	i = 0;
	while (line[i] != '$')
		i++;
	i++;
	var_name = malloc(sizeof(char) * 1000);
	k = 0;
	while(line[i] != ' ' && line[i] != '\0')
	{
		var_name[k] = line[i];
		i++;
		k++;
	}
	var_name[k] = '\0';
	//printf("var_name:%s\n", var_name);
	if (searchlist(data->env_sorted, var_name) != NULL)
		current = searchlist(data->env_sorted, var_name);
	else
	{
		free(var_name);
		return (line);
	}
	free(var_name);
	i = 0;
	k = 0;
	new_str = malloc(sizeof(char) * 1000);
	while (line[i] != '$')
	{
		new_str[k] = line[i];
		i++;
		k++;
	}
	//printf("new_str2:%s\n", new_str);
	i++;
	int j = 0;
	while(current->value[j] != '\0')
	{
		new_str[k] = current->value[j];
		j++;
		k++;
	}
	//printf("new_str3:%s\n", new_str);
	while (line[i] != ' ' && line[i] != '\0')
		i++;
	if(line[i] == '\0')
		return (new_str);
	while (line[i] != '\0')
	{
		new_str[k] = line[i];
		i++;
		k++;
	}
	new_str[k] = '\0';
	//printf("new_str4:%s\n", new_str);

	return (new_str);
}

int		check_dollar_sign(char *line)	//<-changed_23.07.27
{	
	int	i;

	i = 0;
	if(!line)
		return (0);
	while(line[i] != '\0' && line[i] != '\n')
	{
		if(line[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

void	execute_heredoc(t_data *data)	//<-changed_23.07.27
{
	char	*delimiter;
	char	*line;
	
	data->m = 0;
	while (next_heredoc(data) == true)
	{	
		delimiter = data->command_array[data->index][data->m];
		delimiter = trimwhitespace(delimiter);
		data->input = open("tmp/temp.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
		while ((line = readline("> ")) != NULL)
		{
			if (ft_strcmp(line, delimiter) == 0)
				break;
			if(check_dollar_sign(line))
			 	line = dollar_substitution(data, line);
			write(data->input, line, ft_strlen(line));
			write(data->input, "\n", 1);
			free(line);
		}
		//free(line);
		close(data->input);
		data->m += 1;
	}
	data->m += 1;
}
