
#include "../../includes/minishell.h"

void catch_end_of_file(char	*str, t_data *data)		//<-----------------------------added 17.07.2023
{
	int	i;
	int len;

	i = 0;
	len = 0;
	while(str[i] && str[i] != '\0')
	{
		if (str[i] == '<' && str[i+1] == '<')
		{
			data->heredoc_flag = 1;
			break ;
		}
		i++;
	}
	if (data->heredoc_flag != 1)
		return ;
	//printf("data->heredoc_flag on %d= %d\n", i, data->heredoc_flag);
	i++;
	i++;
	//printf("!:%c\n", str[i]);
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	int j = i;
	while(str[i] && str[i] != '\0' && str[i] != ' '&&  str[i] != '\t')		
	{
		len++;
		i++;
	}
	data->heredoc_EOF = malloc(sizeof(char) * (len + 1));
	if(!data->heredoc_EOF)
		return ;
	int m = 0;
	while(str[j] && str[j] != '\0' && str[j] != ' ' && data->heredoc_EOF[m] && data->heredoc_EOF[m] != '\0')
	{
		data->heredoc_EOF[m] = str[j];
		m++;
		j++;
	}
	data->heredoc_EOF[m] = '\0';
	printf("data->heredoc_EOF:%s\n", data->heredoc_EOF);
}


int	create_heredoc(char	*str, t_data *data)
{
	static int	tmp_file;
    char		*line;
	
	if (tmp_file)
		close(tmp_file);
	tmp_file = open("tmpfile", O_CREAT | O_RDWR | O_TRUNC, 0777);
	printf("dat\n");
	if (tmp_file == ERROR)
	{
		printf("Error create heredoc tmp file\n");
		exit (0);
	}	
	// line = readline(">");
    // while(line && ft_strncmp(data->heredoc_EOF, line, ft_strlen(data->heredoc_EOF)))
	// {	//printf("strcmp:%d\n", ft_strncmp(data->heredoc_EOF, line, ft_strlen(data->heredoc_EOF)));
	// 	write(tmp_file, line, ft_strlen(line));
	// 	write(tmp_file, "\n", 1);
	// 	free(line);
	// 	line = readline(">");		
	// }
	close(tmp_file);
}





////////////==========================//////////////
char	*handle_heredoc(char	*str, t_data *data)		//<-----------------------------added 17.07.2023
{	
	catch_end_of_file(str, data);	
	if (data->heredoc_flag != 1)
		return(NULL);
	create_heredoc(str, data);

	return NULL;




//	cat << EOF






	// printf("line:%s\n", line);
	// printf("str:%s\n", str);
	// tmp_str = calloc(sizeof(char), 1000);
	// if (!tmp_str)
	// 	return(NULL);
	// int h = 0;
	// while(str[h] && str[h] != '\0')
	// {
	// 	if (str[h] == '<' && str[h+1] == '<')
	// 		break ;
	// 	tmp_str[h] = str[h];
	// 	//printf("TMP_STR[%d]:%c", h, tmp_str[h]);
	// 	h++;
	// }
	// int v = h;
	// int g = 0;
	// while(line[g] && line[g] != '\0' && tmp_str[h] && tmp_str[h] !='\0')
	// {
	// 	tmp_str[h] = line[g];
	// 	h++;
	// 	g++;
	// }	
	// int y = 0;

	// while (line && line[y] != '\0' && strcmp("EOF", line))
	// {
	// 	tmp_str[h] = line[y];
	// 	h++;
	// 	y++;
	// }
	// v++;
	// v++;
	// int n = 0;
	// while (str[v] && str[v]!= '\0')
	// {	
	// 	while(str[v] == data->heredoc_EOF[n])
	// 	{
	// 		v++;
	// 		n++;			
	// 	}
	// 	if (data->heredoc_EOF[n] == '\0')
	// 		break;
	// 	v++;
	// }
	// while (str[v] != '\0' && str[v])
	// {
	// 	tmp_str[h] = str[v];
	// 	h++;
	// 	v++;
	// }

	// //printf("tmp_str:%s\n", tmp_str);

	// return tmp_str;

}

//	

////////////////////////////////////////////////////////////////////////////////




static bool	next_redirect_in_heredoc(t_data *data)
{
	if (ft_strcmp(data->lexer_output[data->m], "<<") == 0 && data->lexer_output[data->m] != NULL)
	{	
		data->m += 1;
        data->heredoc_EOF = data->lexer_output[data->m];
		data->heredoc_flag = 1;
        //printf("EOF:%s\n", data->heredoc_EOF);
		return (true);
	}
	return (false);
}

static void	redirect_in_from_heredoc(char *filename, t_data *data)
{
	
}



int ft_heredoc(t_data *data)
{
    char	*filename;

	while (next_redirect_in_heredoc(data) == true)
	{
		filename = data->lexer_output[data->m];
		filename = trimwhitespace(filename);
		data->heredoc_filename = filename;
		data->m += 1;
		if (filename == NULL)
		{
			printf("No file");
			exit (0);
		}
		redirect_in_from_heredoc(filename, data);
	}
	return (true);



	// int	redirect(heredoc_args(data))
	// {
	// 	while 



	// }




















// 	int	tmp_file;
// 	char	*line;
	
// 	if (tmp_file)
// 		close(tmp_file);
// 	filename = "tmpfile";
// 	tmp_file = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0777);
// 	if (tmp_file == ERROR)
// 	{
// 		printf("Error open file\n");
// 		exit (0);
// 	}
// 	line = readline(">");	
// 	while (line && strcmp("EOF", line))
// 	{	printf("I'M IN FT_HERD\n");
// 		line = readline(">");
// 		write(tmp_file, line, ft_strlen(line));
// 		free(line);
// 	}
// 	close(tmp_file);
// 	return (0);
// }



// static bool	next_redirect_in_heredoc(t_data *data)
// {
// 	if (ft_strcmp(data->lexer_output[data->m], "<<") == 0 && data->lexer_output[data->m] != NULL)
// 	{	
// 		data->m += 1;
//         data->heredoc_EOF = data->lexer_output[data->m];
// 		data->heredoc_flag = 1;
//         //printf("EOF:%s\n", data->heredoc_EOF);
// 		return (true);
// 	}
// 	return (false);
// }

// static void	redirect_in_from_heredoc(char *filename, t_data *data)
// {
// 	static int	tmp_file;
//     char		*line;
	
// 	if (tmp_file)
// 		close(tmp_file);
// 	tmp_file = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0777);
// 	if (tmp_file== ERROR)
// 	{
// 		printf("Error create heredoc tmp file\n");
// 		exit (0);
// 	}
	
// 	line = readline(">");

//     while(line && ft_strncmp(data->heredoc_EOF, line, ft_strlen(data->heredoc_EOF)))
// 	{	//printf("strcmp:%d\n", ft_strncmp(data->heredoc_EOF, line, ft_strlen(data->heredoc_EOF)));
// 		write(tmp_file, line, ft_strlen(line));
// 		write(tmp_file, "\n", 1);
// 		free(line);
// 		line = readline(">");		
// 	}
// 	close(tmp_file);
// }











// int ft_heredoc(t_data *data)
// {
//     char	*filename;

// 	while (next_redirect_in_heredoc(data) == true)
// 	{
// 		filename = data->lexer_output[data->m];
// 		filename = trimwhitespace(filename);
// 		data->heredoc_filename = filename;
// 		data->m += 1;
// 		if (filename == NULL)
// 		{
// 			printf("No file");
// 			exit (0);
// 		}
// 		//redirect_in_from_heredoc(filename, data);
// 	}
// 	return (true);