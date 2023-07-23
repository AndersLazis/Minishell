/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 23:36:39 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/21 18:29:47 by aputiev          ###   ########.fr       */
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

size_t	ft_strlen(const char *s)
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
	int	j;
	int	k;
	int m;
	t_env_list	*current;
	
	j = 0;
	current = data->env_unsorted;
	while(data->envp[j] != NULL && (current))
	{	
		
		data->envp[j] = malloc((sizeof(char)) * (ft_strlen(current->name) + ft_strlen(current->value) + 2));
		if(!data->envp[j])
			return (EXIT_FAILURE);
		k = 0;
		while(current->name[k] != '\0' && data->envp[j][k] != '\0')
		{
			data->envp[j][k] = current->name[k];
			k++;
		}
		data->envp[j][k] = '=';
		k++;
		m = 0;		

		if (current->value)
		{	
			while(current->value[m] != '\0' && data->envp[j][k] != '\0')
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
	int			i;
	int			j;
	t_env_list	*current;
	char		**new_envp;

	i = 0;
	j = 0;	
	current = data->env_unsorted;
	while(current)
	{
		current = current->next;
		i++;
	}
	new_envp = malloc(sizeof(char*) * (i+1));
	if (!new_envp)
		return (EXIT_FAILURE);
	printf("i:%d\n", i);
	new_envp[i] = NULL;
	data->envp = new_envp;
	//++add free old envp function!!!!
	fill_new_envp_arr(data, i);
	
	///////////////////////////////
	// printf("\n\nnew env:\n");
	// int l = 0;
	// int n = 0;
	// while(data->envp[l] != NULL)
	// {	
	// 	// n = 0;
	// 	// while(data->envp[l][n]!='\0')
	// 	// {
	// 	// 	printf("%c", data->envp[l][n]);
	// 	// 	n++;
	// 	// }
	// 	// printf("\n");
	// 	printf("l:%d,%s\n",l, data->envp[l]);	
	// 	l++;
	// }
	///////////////////////////////env
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
			else												//if wasn't found
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