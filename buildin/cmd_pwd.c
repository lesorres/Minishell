#include "../minishell.h"

void	cmd_pwd(t_all *all)
{
	char	*path;
	char	*tmp;

	path = malloc(PATH_LEN + 1);
	tmp = getcwd(path, PATH_LEN);
	write(1, tmp, ft_strlen(tmp));
	write(1, "\n", 1);
	free(path);
	g_status = 0;
	all = (void *)all;
}
