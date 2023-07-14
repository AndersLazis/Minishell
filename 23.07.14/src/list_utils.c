/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:56:48 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/08 19:49:24 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env_list	*deletenode(t_env_list *curr, char *name)
{
	t_env_list	*next;

	if (curr == NULL)
	{
		return NULL;
	}
	else if (ft_strcmp(curr->name, name) == 0)
	{
		next = curr->next;
		free(curr);
		return next;
	}
	else
	{
		curr->next = deletenode(curr->next, name);
		return curr;
	}
}

t_env_list	*searchlist(t_env_list *data, char *name)
{
	t_env_list	*temp;

	temp = data;
	while(temp != NULL)
	{
		if (strcmp(temp->name, name) == 0)
			return (temp);
		temp=temp->next;
	}
	return (NULL);
}

t_env_list	*sort_list(t_env_list *lst)
{
	t_env_list	*tmp;
	char		*swap_name;
	char		*swap_value;

	tmp = lst;
	while (lst->next != NULL)
	{
		if (ft_strcmp(lst->name, lst->next->name) > 0)
		{
			swap_name = lst->name;
			swap_value = lst->value;
			lst->name = lst->next->name;
			lst->value = lst->next->value;
			lst->next->name = swap_name;
			lst->next->value = swap_value;
			lst = tmp;
		}
		else
			lst = lst->next;
	}
	lst = tmp;
	return (lst);
}

void	insert_at_end(t_env_list *head, char *name, char *value)
{
	t_env_list	*node;
	t_env_list	*current;

	node = malloc(sizeof(t_env_list));
	node->name = name;
	node->value = value;
	node->next = NULL;
	current = head;
	while (current->next != NULL)
		current = current->next;
	current->next = node;
}
