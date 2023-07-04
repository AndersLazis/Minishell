/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_unsorted.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 23:31:51 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/04 21:02:10 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	init_env_unsorted(t_data *data, char **env)
{
	t_env	*new;
	t_env	*current;
	t_env	*head;
	int				i;
	
	i = 0;
	head = malloc(sizeof(t_env));
	if(!head)
		return(EXIT_FAILURE);
	current = head;
	print_env(env);//
	printf("============================\n");//
	current->name = ft_strdup_name(env[0]);
	current->value = ft_strdup_value(env[0]);
	current->next = NULL;
	data->env = current;
	i = 1;
	while(env && env[0] && env[i])
	{
		new = malloc(sizeof(t_env_sorted));
		if(!new)
			return(EXIT_FAILURE);
		new->name = ft_strdup_name(env[i]);
		new->value = ft_strdup_value(env[i]);
		current->next = new;
		current = current->next;
		i++;
	}
	
	// current = data->env;
	// while(current)
	// {	
	// 	printf("%s=%s\n", current->name, current->value);		
	// 	if(current->next == NULL)
	// 		break;
	// 	current = current->next;
	// }	
	return(0);
}
