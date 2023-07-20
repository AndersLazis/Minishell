/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_arguments.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 00:31:34 by mschulme          #+#    #+#             */
/*   Updated: 2023/07/16 19:52:11 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Code is only working for spaces

static int	ft_countparts(char const *s)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == ' ')
			i++;
		if (s[i] != ' ' && s[i] != '\0')
			count++;
		while (s[i] != ' ' && s[i] != '\0')
			i++;
	}
	return (count);
}

static char	*ft_mallocwords(char *str, t_data *data)
{
	char	*str_save;
	int		j;
	
	j = 0;
	str_save = ft_calloc(1000, 1);
	while (str[data->i] != ' ' && str[data->i] != 0)
	{
		while (str[data->i] != ' ' && str[data->i] != '\'' && str[data->i] != '\"' && str[data->i] != 0)
		{
			str_save[j] = str[data->i];
			j++;
			data->i += 1;
		}
		if (str[data->i] == '\"')
		{
			(data->i)++;
			while (str[data->i] != '\"' && str[data->i] != 0)
			{
				str_save[j] = str[data->i];
				j++;
				data->i += 1;
			}
			(data->i)++;
		}
		if (str[data->i] == '\'')
		{
			(data->i)++;
			while (str[data->i] != '\'' && str[data->i] != 0)
			{
				if (str[data->i] != '\'')
					str_save[j] = str[data->i];
				j++;
				data->i += 1;
			}
			(data->i)++;
		}
		
	}
	return(str_save);
}

static void	ft_free(char **strs, t_data *data)
{
	while ((data->j)-- > 0)
		free(strs[data->j]);
	free(strs);
}

char	**ft_split_arguments(char *str, t_data *data)
{
	int		wordcount;
	char	**strs;
	
	data->i = 0;
	data->j = 0;
	wordcount = ft_countparts(str);
	strs = malloc((wordcount + 1) * sizeof (char*));
	if (!strs)
		return (NULL);
	while (str[data->i] != 0)
	{
		while (str[data->i] == ' ' && str[data->i] != 0)
			(data->i)++;
		if (str[data->i] == '\0')
			break ;
		strs[data->j] = ft_mallocwords(str, data);
		if (strs[data->j] == NULL)
		{
			ft_free(strs, data);
			return (NULL);
		}
		(data->j)++;
	}
	strs[data->j] = NULL;
	return (strs);
}

char	**ft_split_arguments_with_heredoc(char *str, t_data *data)
{
	int		wordcount;
	char	**strs;
	
	data->i = 0;
	data->j = 0;



	static int	tmp_file;
    char		*line;
	
	if (tmp_file)
		close(tmp_file);
	tmp_file = open(data->heredoc_filename, O_RDONLY, 0777);
	if (tmp_file== ERROR)
	{
		printf("Error open heredoc tmp file\n");
		exit (0);
	}
	dup2(STDIN_FILENO, tmp_file);
    while(line && ft_strncmp(data->heredoc_EOF, line, ft_strlen(data->heredoc_EOF)))
	{	//printf("strcmp:%d\n", ft_strncmp(data->heredoc_EOF, line, ft_strlen(data->heredoc_EOF)));
				
		line = readline(">");
		printf("%s", line);	
		free(line);
	}
	close(tmp_file);
}



	
	// wordcount = ft_countparts(str);




	// strs = malloc((wordcount + 1) * sizeof (char*));
	// if (!strs)
	// 	return (NULL);
	// while (str[data->i] != 0)
	// {
	// 	while (str[data->i] == ' ' && str[data->i] != 0)
	// 		(data->i)++;
	// 	if (str[data->i] == '\0')
	// 		break ;
	// 	strs[data->j] = ft_mallocwords(str, data);
	// 	if (strs[data->j] == NULL)
	// 	{
	// 		ft_free(strs, data);
	// 		return (NULL);
	// 	}
	// 	(data->j)++;
	// }
	// strs[data->j] = NULL;
	// return (strs);

