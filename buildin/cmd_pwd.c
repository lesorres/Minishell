#include "../minishell.h"

void    cmd_pwd(t_all *all, char **envp)    // ok???
{
	char    *path;
	char    *tmp;

	path = malloc(PATH_LEN + 1);
	tmp = getcwd(path, PATH_LEN);
	write(1, tmp, ft_strlen(tmp));
	write(1, "\n", 1);
	free(path);
	status = 0;
}