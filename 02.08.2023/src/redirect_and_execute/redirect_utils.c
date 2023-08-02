/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 21:18:11 by mschulme          #+#    #+#             */
/*   Updated: 2023/08/02 17:14:50 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**my_realloc(char **old_arr, size_t new_size)
{
	char	**new_arr;
	int		i;

	if (old_arr == NULL)
		return (malloc(new_size));
	new_arr = malloc(new_size);
	if (new_arr == NULL)
		exit (EXIT_FAILURE);
	i = 0;
	while (old_arr[i] != NULL)
	{
		new_arr[i] = old_arr[i];
		i++;
	}
	return (new_arr);
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
	array = my_realloc(array, (size + 2) * sizeof(char **));
	array[size] = malloc(ft_strlen(string) + 1);
	if (array[size] == NULL)
		exit (EXIT_FAILURE);
	ft_strlcpy(array[size], string, 1000);
	size += 1;
	array[size] = NULL;
	return (array);
}
