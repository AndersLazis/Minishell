
#include "../includes/minishell.h"



int	pwd(void)
{
	char	buf[PATH_MAX];

	if (!(getcwd(buf, sizeof(buf)) != NULL))
		return (-1);
	printf("%s\n", buf);
	return 0;
}










