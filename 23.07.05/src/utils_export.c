
#include "../includes/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

/*===========================CHECK IF ENV VARIABLE NAME VALID=================================*/
int		is_env_var_name_valid(char *args)
{
	int	i;
	int	quotes;
	int	double_quotes;
	i = 0;

	while(args[i] != '\0' && args[i] != '=')
	{
		if ((args[0] != '_' && args[0] != 34 && args[0] != 39) && (!(args[0] >= 'a' && args[0] <= 'z')) && (!(args[0] >= 'A' && args[0] <= 'Z')))
			return (0);
		if ((args[i] != '_' && args[0] != 34 && args[0] != 39) && (args[i] < '0' && args[i] > '9') && (args[i] < 'a' && args[i] > 'z') && (args[i] < 'A' && args[i] > 'Z'))
			return (0);
		i++;
	}
	return (1);
}
/*===============================================================================================*/




/*===========================CHECK IF ENV VARIABLE IS ALREADY EXISTS=================================*/
int is_env_var_exist(char *args, t_data *data)
{	
	int	i;
	int	j;
	t_env_unsorted *current;

	current = data->env_unsorted;	
	while(current->next != NULL)
	{	
		i = 0;
		j = 0;
		while(args[i] == ' ' || args[i] == '\'' || args[i] == '\"' || args[i] == '\t')
			i++;
		// printf("args:%s\n", args);
		// printf("current->name:%s\n", current->name);
		while(args[i] != '\0' && args[i] != '=')
		{
			if(current->name[j] != args[i])
				break;
			i++;
			j++;
		}
		if(args[i] == '\0' || args[i] == '=')
			return(1);
		current=current->next;
	}
	return(0);
}
/*===============================================================================================*/




/*===========================CHECK IF THE QUOTES ARE CLOSED=================================*/
int		is_quotes_are_closed(char *args)
{	
	int	i;
	int	quotes;
	int	double_quotes;
	i = 0;
	quotes = 0;
	double_quotes = 0;
	while(args[i] != '\0')
	{
		if (args[i] == 39)
			quotes++;
		if (args[i] == 34)
			double_quotes++;
		i++;
	}
	if (quotes%2 || double_quotes%2)
		return (0);
	return (1);
}
/*===============================================================================================*/
