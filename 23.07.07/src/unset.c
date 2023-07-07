

#include "../includes/minishell.h"

/*========================================REMOVE VARIABLE==============================================*/
/* removes environment variable from the unsorted list*/
int remove_env_var_in_unsorted(char *args,t_data *data)
{
	printf("remove in unsorted\n");
	int	i;
	int	j;
	int counter;
	t_env_unsorted *current;
	t_env_unsorted *previous;

	current = data->env_unsorted;
	counter = 0;
	while(current)
	{	
		i = 0;
		j = 0;
		while(args[i] == ' ' || args[i] == '\'' || args[i] == '\"' || args[i] == '\t')
			i++;
		while(args[i] != '\0' && args[i] != '=')
		{			
			if(current->name[j] != args[i])				
				break;
			i++;
			j++;
		}
		if(args[i] == '\0' || args[i] == '=')
		{
			if(counter == 0) //1st case (var in begin of the link list)
				data->env_unsorted = current->next;
			else if(previous && current->next != NULL) //2nd case (var in middle of the link list)
				previous->next = current->next;
			else if(previous && current->next == NULL) //3rd case (var in the end of the link list)
				previous->next = NULL;
			free(current);
			return (1);			
		}
		previous=current;
		current=current->next;
		counter++;
	}
	return (0);
}

/* removes environment variable from the sorted list*/

int remove_env_var_in_sorted(char *args,t_data *data)
{
	printf("remove in sorted\n");
	int	i;
	int	j;
	int counter;
	t_env_sorted *current;
	t_env_sorted *previous;

	current = data->env_sorted;
	counter = 0;
	while(current)
	{	
		i = 0;
		j = 0;
		while(args[i] == ' ' || args[i] == '\'' || args[i] == '\"' || args[i] == '\t')
			i++;
		while(args[i] != '\0' && args[i] != '=')
		{			
			if(current->name[j] != args[i])				
				break;
			i++;
			j++;
		}
		if(args[i] == '\0' || args[i] == '=')
		{
			if(counter == 0) //1st case (var in begin of the link list)
				data->env_sorted = current->next;
			else if(previous && current->next != NULL) //2nd case (var in middle of the link list)
				previous->next = current->next;
			else if(previous && current->next == NULL) //3rd case (var in the end of the link list)
				previous->next = NULL;
			free(current);
			return (1);
			
		}
		previous=current;
		current=current->next;
		counter++;
	}
	return (0);
}








/*=============================================UNSET=============================================*/
int	ft_unset(char *args,t_data *data)
{
	t_env_sorted	*current;
	printf("Unset-args:|%s|\n", args);
	current = data->env_sorted;
	if(!args)
		return(EXIT_SUCCESS);
	else
	{
		if(!is_env_var_name_valid(args))
		{	
			printf("UNSET: `%s': not a valid identifier\n", args);
			return (EXIT_FAILURE);
		}
		// if(!is_quotes_are_closed(args))
		// {	
		// 	printf("minishell: printf: `%s': invalid format character\n", args);
		// 	return (EXIT_FAILURE);
		// }
		//printf("is_env_var_exist:%d\n", is_env_var_exist(args, data));
		if(is_env_var_exist(args, data) == 1)
		{
			printf("remove_env_var_in_sorted=%d\n", remove_env_var_in_sorted(args, data));
			printf("add_new_env_var_in_unsorted=%d\n", remove_env_var_in_unsorted(args, data));
		}
		else
		{
			return(EXIT_SUCCESS);
		}
	}	
	return (EXIT_SUCCESS);
}
/*=========================================================================================================*/

//printf("I AM HERE!\n");
