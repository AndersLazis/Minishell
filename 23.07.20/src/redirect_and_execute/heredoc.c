/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 20:05:20 by aputiev           #+#    #+#             */
/*   Updated: 2023/07/17 20:10:04 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Checks if the heredoc sign "<<" exist in input */
int	heredoc_exist(char	*str, t_data *data)
{
	int	i;
	int len;

	i = 0;
	len = 0;
	if(!str)
		return (0) ;
	while(str[i] && str[i] != '\0')
	{
		if (str[i] == '<' && str[i+1] == '<')
		{
			data->heredoc_flag = 1;
			return(1);
		}
		i++;
	}
	if (data->heredoc_flag != 1)
		return (0) ;
	return (1) ;
}

/* Catches end-of-file delimeter and saves it in "t_data data" */
int catch_end_of_file(char	*str, t_data *data)
{	
	int	i;
	int j;
	int	eof_len;

	i = 0;
	eof_len = 0;
	while(str[i] && str[i] != '\0')
	{
		if (str[i] == '<' && str[i+1] == '<')
			break ;
		i++;
	}
	i = i + 2;
	//printf("data->heredoc_flag on %d= %d\n", i, data->heredoc_flag);
	//printf("!:%c\n", str[i]);
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	j = i;
	while(str[i] && str[i] != '\0' && str[i] != ' '&&  str[i] != '\t')		
	{
		eof_len++;
		i++;
	}
	data->heredoc_EOF = malloc(sizeof(char) * (eof_len + 1));
	if(!data->heredoc_EOF)
		return(EXIT_FAILURE);
	i = 0;
	while(str[j] && str[j] != '\0' && str[j] != ' ' && str[j] != '\t' && data->heredoc_EOF[i] && data->heredoc_EOF[i] != '\0')
	{
		data->heredoc_EOF[i] = str[j];
		i++;
		j++;
	}
	data->heredoc_EOF[i] = '\0';
	//printf("data->heredoc_EOF:%s\n", data->heredoc_EOF);
	return(EXIT_SUCCESS);
}

/* Opens a temporary file and writes there lines from input */
int	create_heredoc(char	*str, t_data *data)
{
	static int	tmp_file;
    char		*line;
	
	if (tmp_file)
		close(tmp_file);
	tmp_file = open("build/tmp_file", O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (tmp_file== ERROR)
	{
		printf("Error create heredoc tmp file\n");
		return (EXIT_FAILURE);
	}	
	line = readline(">");
    while(line && ft_strncmp(data->heredoc_EOF, line, ft_strlen(data->heredoc_EOF)))
	{
		write(tmp_file, line, ft_strlen(line));
		write(tmp_file, "\n", 1);
		free(line);
		line = readline(">");		
	}
	free(line);
	close(tmp_file);
	return (EXIT_SUCCESS);
}

/* changes input string, replacing <<EOF by tmp filename */
char *implement_heredoc(char	*str, t_data *data)	
{
	char	*tmp_str;
	char	*ptr;
	int	i;
	int	j;
	char	*tmpfile = "build/tmp_file";

	tmp_str = malloc(sizeof(char)*(strlen(str) + 1 + 14));
	if (!tmp_str)
		return(NULL);
	i = 0;
	while(str[i] && str[i] != '\0')
	{
		if (str[i] == '<' && str[i+1] == '<')
			break ;
		tmp_str[i] = str[i];
		i++;
	}
	j = 0;
	while(tmpfile[j] != '\0')
	{
		tmp_str[i] = tmpfile[j];
		i++;
		j++;
	}
	tmp_str[i] = '\0';

	printf("tmp_str:%s\n", tmp_str);
	return(tmp_str);
}

/* main heredoc function */
char *handle_heredoc(char	*str, t_data *data)
{	
	char *tmp_str;

	catch_end_of_file(str, data);	
	if (data->heredoc_flag != 1)
		return(NULL);
	if(create_heredoc(str, data) == EXIT_FAILURE)
		exit (0);
	tmp_str = implement_heredoc(str, data);
	if (tmp_str == NULL)
		exit (0);
	return(tmp_str);
}
