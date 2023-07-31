/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 21:18:11 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/31 01:33:46 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*my_realloc(void *ptr, size_t new_size)
{
	void	*new_ptr;

	if (ptr == NULL)
	{
		return (malloc(new_size));
	}
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
	{
		return (NULL);
	}
	ft_memcpy(new_ptr, ptr, new_size);
	free(ptr);
	return (new_ptr);
}

char	**add_string(char **array, char *string)
{
	int	size;

	size = 0;
	if (array == NULL)
		size = 0;
	else
	{
		while (array[size] != NULL)
			size++;
	}
	array = my_realloc(array, (size + 2) * sizeof(char *));
	array[size] = malloc(ft_strlen(string) + 1);
	ft_strlcpy(array[size], string, 1000);
	size += 1;
	array[size] = NULL;
	return (array);
}
