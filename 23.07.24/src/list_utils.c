/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:56:48 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/22 13:14:52 by aputiev          ###   ########.fr       */
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
	node->name = strdup(name);
	node->value = strdup(value);
	node->next = NULL;
	current = head;
	while (current->next != NULL)
		current = current->next;
	current->next = node;
}

void	create_old_pwd(t_env_list *head, char* old_pwd)
{
	t_env_list	*node;
	t_env_list	*current;
	char		*oldpwd = "OLDPWD";
	
	node = malloc(sizeof(t_env_list));
	node->name = malloc(sizeof(char) * 7);
	strcpy(node->name, oldpwd);
	node->name[6] = '\0';
	if(old_pwd == NULL)
		node->value = NULL;
	else
		node->value = old_pwd;
	node->next = NULL;
	current = head;
	while (current->next != NULL)
		current = current->next;
	current->next = node;
}

void	create_shlvl(t_env_list *head)
{
	t_env_list	*node;
	t_env_list	*current;
	char	*shlvl = "SHLVL";
	node = malloc(sizeof(t_env_list));
	node->name = malloc(sizeof(char) * 6);
	strcpy(node->name, shlvl);
	node->name[5] = '\0';
	//node->value = 1;							//<-changed_22.07.23
	node->value = malloc(sizeof(char) * 2);		//<-changed_22.07.23
	node->value[0] = '1';						//<-changed_22.07.23
	node->value[1] = '\0';						//<-changed_22.07.23
	node->next = NULL;
	current = head;
	while (current->next != NULL)
		current = current->next;
	current->next = node;
}
