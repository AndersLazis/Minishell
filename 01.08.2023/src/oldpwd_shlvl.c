/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oldpwd_shlvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 01:31:38 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/31 00:09:36 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_old_pwd(t_env_list *head, char *old_pwd)
{
	t_env_list	*node;
	t_env_list	*current;
	static char	*oldpwd = "OLDPWD";

	node = malloc(sizeof(t_env_list));
	node->name = malloc(sizeof(char) * 7);
	strcpy(node->name, oldpwd);
	node->name[6] = '\0';
	if (old_pwd == NULL)
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
	t_env_list	*current;
	t_env_list	*node;
	static char	*shlvl = "SHLVL";

	node = malloc(sizeof(t_env_list));
	node->name = malloc(sizeof(char) * 6);
	strcpy(node->name, shlvl);
	node->name[5] = '\0';
	node->value = malloc(sizeof(char) * 2);
	node->value[0] = '1';
	node->value[1] = '\0';
	node->next = NULL;
	current = head;
	while (current->next != NULL)
		current = current->next;
	current->next = node;
}
