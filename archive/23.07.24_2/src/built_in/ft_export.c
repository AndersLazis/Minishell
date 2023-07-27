/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 23:36:39 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/24 18:45:04 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_sorted_list(t_env_list *current)
{
	t_env_list *temp;

	temp = current;
	while(temp)
	{	
		if(current->value == NULL)
			printf("%s=%s\n", current->name, "\"\"");
		else
			printf("declare -x %s=\"%s\"\n", temp->name, temp->value);
		temp = temp->next;
	}
}

size_t	ft_strlen(const char *s) // Change in libft
{
	size_t	count;

	count = 0;
	if(!s)
		return(0);
	while (*s++)
		count++;
	return (count);
}

int fill_new_envp_arr(t_data *data, int i)
{
	t_env_list	*current;
	int	j;
	int	k;
	int	m;

	j = 0;
	current = data->env_unsorted;
	while(i-- && current)
	{	
		data->envp[j] = ft_calloc(1, ft_strlen(current->name) + ft_strlen(current->value) + 2);
		if(!data->envp[j])
			return (EXIT_FAILURE);
		k = 0;
		while(current->name[k] != '\0')
		{
			data->envp[j][k] = current->name[k];
			k++;
		}
		data->envp[j][k] = '=';
		k++;
		m = 0;
		if (current->value)
		{	
			while(current->value[m] != '\0')
			{
				data->envp[j][k] = current->value[m];
				k++;
				m++;
			}
		}
		data->envp[j][k] = '\0';
		j++;
		current = current->next;
	}
	data->envp[j] = NULL;
	return (0);
}

int	update_envp(t_data *data)
{
	char		**new_envp;
	int			i;
	int			j;
	t_env_list	*current;
	
	i = 0;
	j = 0;	
	
	while(data->envp && data->envp[i]!=NULL)  //<-changed_23.07.24
	{
		free(data->envp[i]);
		i++;
	}	
	if(data->envp)
	 	free(data->envp);   //<-changed_23.07.24
	i = 0;
	current = data->env_unsorted;
	while (current)
	{
		current = current->next;
		i++;
	}
	new_envp = malloc(sizeof(char*) * (i + 1));
	if (!new_envp)
		return (EXIT_FAILURE);
	new_envp[i] = NULL;
	
	data->envp = new_envp;
	fill_new_envp_arr(data, i);
	
	return(0);
}

void	ft_export(t_data *data)
{
	t_env_list	*current;
	char		*name;
	char		*val;
	int			i;
	
	i= 1;
	if (data->split[1] == NULL)
		print_sorted_list(data->env_sorted);
	else
	{	
		if(!is_env_var_name_valid(data->split))
			return ;	
		while (data->split[i] != NULL)
		{	printf("data->split[%d]|%s|\n", i, data->split[i]);
			
			name = ft_strdup_name(data->split[i]);
			val = ft_strdup_value(data->split[i]);
			if (searchlist(data->env_sorted, name) != NULL)	//if found
			{
				current = searchlist(data->env_sorted, name);
				current->value = ft_strdup_value(data->split[i]);
				current = searchlist(data->env_unsorted, name);
				current->value = ft_strdup_value(data->split[i]);
			}
			else
			{
				insert_at_end(data->env_sorted, name, val);
				data->env_sorted = sort_list(data->env_sorted);
				insert_at_end(data->env_unsorted, name, val);
			}
			i++;
		}
	}
	update_envp(data);
}