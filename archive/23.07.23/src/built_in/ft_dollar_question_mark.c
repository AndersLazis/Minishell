/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar_question_mark.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 15:45:25 by aputiev           #+#    #+#             */
/*   Updated: 2023/07/23 19:15:49 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* detects "$?" sign in command line */
int	dollar_questionmark_exist(char *str, t_data *data)
{	
	int	i;
	int len;

	i = 0;
	len = 0;
	if(!str)
		return (0) ;
	update_last_exit_code(str, data);
	while(str[i] && str[i] != '\0')
	{
		if (str[i] == '$' && str[i+1] == '?')
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

/* main heredoc function */
char *handle_dollar_questionmark(char *str, t_data *data)
{	
	char *tmp_str;
	int exit_code;

	exit_code = data->exit_code;
	if(WIFEXITED(exit_code))
		tmp_str = implement_dollar_questionmark(str, (WEXITSTATUS(exit_code)));
	if (tmp_str == NULL)
		exit (EXIT_FAILURE);
	return(tmp_str);
}


////////////////////////////////////////////////////////////////////////////////////////




/* Catches end-of-file delimeter and saves it in "t_data data" */
int catch_end_of_file(char	*str, t_data *data)
{	
	int	i;
	int j;
	int	eof_len;
	
	i = 0;
	eof_len = 0;
	
	//cat <<eof
	printf("INPUT FOR catch_end_of_file:%s\n", str);
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
	printf("!i:%d, len:%d", i, eof_len);
	data->heredoc_EOF = malloc(sizeof(char) * (eof_len + 1));
	if(!data->heredoc_EOF)
		return(EXIT_FAILURE);
	i = 0;
	printf("!i:%d, j:%d, len:%d", i, j, eof_len);
	while(str[j] && str[j] != '\0' && str[j] != ' ' && str[j] != '\t')
	{
		data->heredoc_EOF[i] = str[j];
		i++;
		j++;
	}
	data->heredoc_EOF[i] = '\0';
	printf("data->heredoc_EOF:|%s|\n", data->heredoc_EOF);
	return(EXIT_SUCCESS);
}

/* Opens a temporary file and writes there lines from input */
int	create_heredoc(t_data *data)
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
char *implement_heredoc(char	*str)	
{
	char	*tmp_str;
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

