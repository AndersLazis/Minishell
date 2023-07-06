
#include "../includes/minishell.h"

/*========================================PRINT==============================================*/
/* Prints unsorted list */
int print_unsorted_list(t_data *data)
{
	t_env_unsorted	*current;

	current = data->env_unsorted;
	while(current->next != NULL)
	{
		printf("%s=%s\n", current->name, current->value);			
		current = current->next;
	}
	return (0);
}
/* Prints sorted list */
int print_sorted_list(t_data *data)
{
	t_env_sorted	*current;

	current = data->env_sorted;
	while(current->next != NULL)
	{
		printf("declare -x %s=\"%s\"\n", current->name, current->value);			
		current = current->next;
	}
	return (0);
}
/*===============================================================================================*/





/*========================================REWRITE==============================================*/
int	rewrite_exist_env_var_in_sorted(char *args,t_data *data)
{
	printf("REWRITE\n");
	int	i;
	int	j;
	t_env_sorted *current;

	current = data->env_sorted;	
	while(current->next != NULL)
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
			current->value = ft_strdup_value(args);
			return (1);
		}
		current=current->next;
	}
	return (0);
}

int	rewrite_exist_env_var_in_unsorted(char *args,t_data *data)
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
		while(args[i] != '\0' && args[i] != '=')
		{			
			if(current->name[j] != args[i])				
				break;
			i++;
			j++;
		}
		printf("I AM:%c\n", args[i]);
		printf("NAME:%c\n", current->name[j]);
		if(args[i] == '\0' || args[i] == '=')
		{
			current->value = ft_strdup_value(args);
			return (1);
		}
		current=current->next;
	}
	return (0);
}

/*===============================================================================================*/














/*========================================ADD NEW VARIABLE==============================================*/
/* adds new environment variable into the unsorted list*/
int add_new_env_var_in_unsorted(char *args, t_data *data)
{	
	t_env_unsorted	*current;
	t_env_unsorted	*new;
	
	current = data->env_unsorted;	
	while(current->next != NULL)	
		current=current->next;
	new = malloc(sizeof(t_env_unsorted));
	current->next = new;
	new->next = NULL;
	new->name = ft_strdup_name(args);
	new->value = ft_strdup_value(args);
	// current = data->env_unsorted;	
	// while(current != NULL)	
	// 	current=current->next;
	return(0);
}

/* adds new environment variable into the sorted list*/
int add_new_env_var_in_sorted(char *args,t_data *data)
{	
	t_env_sorted	*current;
	t_env_sorted	*new;

	char	*name = ft_strdup_name(args);
	char	*value = ft_strdup_value(args);
	
	current = data->env_sorted;
	
	while(current->next != NULL)
	{	//printf("current->next->name|%s|\n", current->next->name);
		if((strcmp(name, current->name) > 0) && (strcmp(name, current->next->name) < 0))
		{	//printf("Ja, motherf*cker!\n");
			new = malloc(sizeof(t_env_sorted));
			current->next = new;
			new->next = NULL;			
			new->name = name;
			new->value = value;
			return(1);
			// new->name = ft_strdup_name(args);
			// new->value = ft_strdup_value(args);	
		}
		current=current->next;		
	}
	if(current->next == NULL)
	{	
		new = malloc(sizeof(t_env_sorted));
		current->next = new;
		new->next = NULL;
		new->name = ft_strdup_name(args);
		new->value = ft_strdup_value(args);
		return(2);	
	}
	return(0);
}
/*===============================================================================================*/
//	export xc=1





/*=============================================EXPORT=============================================*/
int	ft_export(char *args,t_data *data)
{
	t_env_sorted	*current;
	int errno;
	printf("INPUT export-args:|%s|\n", args);
	errno = 0;
	current = data->env_sorted;
	// printf("=====export_args=====:%s\n", args); //<---Check input arguments to export function (for test purposes);
	if(!args)
	{	
		printf("==================EXPORT NO ARGS========================\n");
		print_sorted_list(data);
		printf("===================================================\n");
	}
	else
	{
		if(!is_env_var_name_valid(args))
		{	
			printf("export: `%s': not a valid identifier\n", args);
			return (EXIT_FAILURE);
		}
		// if(!is_quotes_are_closed(args))
		// {	
		// 	printf("minishell: printf: `%s': invalid format character\n", args);
		// 	return (EXIT_FAILURE);
		// }
		printf("%d\n", is_env_var_exist(args, data));
		if(is_env_var_exist(args, data) == 0)
		{
			printf("add_new_env_var_in_sorted=%d\n", add_new_env_var_in_sorted(args, data));
			printf("add_new_env_var_in_unsorted=%d\n", add_new_env_var_in_unsorted(args, data));
		}
		else
		{
			printf("unsort===%d\n", rewrite_exist_env_var_in_unsorted(args, data));
			printf("sort===%d\n", rewrite_exist_env_var_in_sorted(args, data));			
		}
		printf("==================print_unsorted_list========================\n");
		print_unsorted_list(data); //<---for testing purposes
		printf("===================================================\n");

	}	
	return (EXIT_SUCCESS);
}
/*=========================================================================================================*/

//printf("I AM HERE!\n");
