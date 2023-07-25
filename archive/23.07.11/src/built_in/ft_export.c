/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 23:36:39 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/13 13:04:17 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_sorted_list(t_env_list *current) //<------------------------------------------------------changed_july_12
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



int	add_var_in_envp(t_data *data, char *name, char *val)
{
	int		i;
	int		j;
	int		len;
	char	**temp;
	
	i = 0;
	
	while(data->envp[i] != NULL)
		i++;
	temp = malloc(sizeof(char*) * (i + 2));
	if(!temp)
		return(1);
	i = 0;
	j = 0;
	while(data->envp[i] != NULL)
	{	
		len = 0;
		while(data->envp[i][j]!= '\0')
			len++;
		while(data->envp[i][j] != '\0')
		{	
			temp[i] = malloc(sizeof(char)*)
			temp[i][j] = envp[i][j];
			j++;
		}
		i++;
	}
	
	//free envp

	
}






int	update_envp(t_data *data, char *name, char *val)
{	

	int		i;
	int		j;

	i = 0;
	j = 0;
	
	while(data->envp[i] != NULL)
	{	//printf("data->envp[i]%s\n", data->envp[i]);
		while(data->envp[i][j] != '\0' && data->envp[i][j] != '=' && name[j] != '\0')
		{
			if(data->envp[i][j] != name[j])
				break ;
			j++;		
		}
		if(data->envp[i][j] == '=')		
		{	//printf("data->envp[i][j-1]%c\n", data->envp[i][j-1]);
			// 	printf("data->envp[i][j]%c\n", data->envp[i][j]);
			printf("//rewrite_var_in_envp(data, name, val);\n");
			return (0);
		}
		i++;
	}
	printf("//add_var_in_envp(data, name, val);");
	return(0);
}


void	ft_export(t_data *data) //<------------------------------------------------------changed_july_12
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
		while (data->split[i] != NULL)
		{
			if(!is_env_var_name_valid(data))
			{	
				printf("export: `%s': not a valid identifier\n", data->split[i]);
				return ;
			}
			name = ft_strdup_name(data->split[i]);
			val = ft_strdup_value(data->split[i]);
			if (searchlist(data->env_sorted, name) != NULL)
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
	update_envp(data, name, val);
}
