
#include "../includes/minishell.h"

void print_env(char **env) //<-for test purposes
{
	int i = 0;
	while(env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}

int	ft_env(t_data *data)
{
	t_env_unsorted *current;
	current = data->env_unsorted;
		printf("============ENV START HERE ================\n");//
	while(current)
	{	
		printf("%s=%s\n", current->name, current->value);		
		if(current->next == NULL)
			{break;}
		current = current->next;
	}
		printf("============ENV END HERE ================\n");//
	
	return (0);
}