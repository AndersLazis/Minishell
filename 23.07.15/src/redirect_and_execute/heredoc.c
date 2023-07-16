
#include "../../includes/minishell.h"

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
	static int	tmp_file;
    char		*line;
	
	if (tmp_file)
		close(tmp_file);
	tmp_file = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (tmp_file== ERROR)
	{
		printf("Error create heredoc tmp file\n");
		exit (0);
	}
	
	line = readline(">");

    while(line && ft_strncmp(data->heredoc_EOF, line, ft_strlen(data->heredoc_EOF)))
	{	//printf("strcmp:%d\n", ft_strncmp(data->heredoc_EOF, line, ft_strlen(data->heredoc_EOF)));
		write(tmp_file, line, ft_strlen(line));
		write(tmp_file, "\n", 1);
		free(line);
		line = readline(">");		
	}
	close(tmp_file);
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
























	int	tmp_file;
	char	*line;
	
	if (tmp_file)
		close(tmp_file);
	filename = "tmpfile";
	tmp_file = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (tmp_file == ERROR)
	{
		printf("Error open file\n");
		exit (0);
	}
	line = readline(">");	
	while (line && strcmp("EOF", line))
	{	printf("I'M IN FT_HERD\n");
		line = readline(">");
		write(tmp_file, line, ft_strlen(line));
		free(line);
	}
	close(tmp_file);
	return (0);
}
