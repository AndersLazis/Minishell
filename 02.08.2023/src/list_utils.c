/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:56:48 by mschulme          #+#    #+#             */
/*   Updated: 2023/08/01 21:57:13 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env_list	*deletenode(t_env_list *curr, char *name)
{
	t_env_list	*next;

	if (curr == NULL)
	{
		return (NULL);
	}
	else if (ft_strcmp(curr->name, name) == 0)
	{
		next = curr->next;
		free(curr);
		return (next);
	}
	else
	{
		curr->next = deletenode(curr->next, name);
		return (curr);
	}
}

t_env_list	*searchlist(t_env_list *data, char *name)
{
	t_env_list	*temp;

	temp = data;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->name, name) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

t_env_list	*swap_list_operation(t_env_list *lst, t_env_list *tmp)
{
	char		*swap_name;
	char		*swap_value;
	int			swap_equal_sign;

	swap_name = lst->name;
	swap_value = lst->value;
	swap_equal_sign = lst->equal_sign;
	lst->name = lst->next->name;
	lst->value = lst->next->value;
	lst->equal_sign = lst->next->equal_sign;
	lst->next->name = swap_name;
	lst->next->value = swap_value;
	lst->next->equal_sign = swap_equal_sign;
	lst = tmp;
	return (lst);
}

t_env_list	*sort_list(t_env_list *lst)
{
	t_env_list	*tmp;

	tmp = lst;
	while (lst->next != NULL)
	{
		if (ft_strcmp(lst->name, lst->next->name) > 0)
			lst = swap_list_operation(lst, tmp);
		else
			lst = lst->next;
	}
	lst = tmp;
	return (lst);
}

void	insert_at_end(t_env_list *head, char *name, char *value, int equal_sign)
{
	t_env_list	*node;
	t_env_list	*current;

	node = malloc(sizeof(t_env_list));
	node->name = ft_strdup(name);
	node->value = ft_strdup(value);
	node->equal_sign = equal_sign;
	node->next = NULL;
	current = head;
	while (current->next != NULL)
		current = current->next;
	current->next = node;
}
