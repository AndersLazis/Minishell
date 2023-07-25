/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 13:27:48 by aputiev           #+#    #+#             */
/*   Updated: 2023/06/29 12:40:52 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	main(int ac, char **av, char **envp)
// {
// 	env(envp);
// 	return (0);
// }


int	pwd(void)
{
	char	buf[PATH_MAX];

	if (!(getcwd(buf, sizeof(buf)) != NULL))
		return (-1);
	return 0;
}

int	env(char **envp)
{
	int	i;
	char	*env_var;
	
	i = 0;
	env_var = envp[i];
	while(env_var != NULL)
	{
		printf("%s\n", env_var);
		i++;
		env_var = envp[i];
	}
	return (0);
}
