#include "../minishell.h"

void    get_envp(t_all *all, char **envp)  // ок
{
	int     line;
	
	all->tline.env_line_num = 0;
	line = 0;
	while (envp[all->tline.env_line_num])
		all->tline.env_line_num++;
	all->tline.env_arr = (char **)malloc(sizeof(char *) * (all->tline.env_line_num));
	while (line < all->tline.env_line_num)
	{
		all->tline.env_arr[line] = ft_strdup(envp[line]);
		line++;
	}
	all->tline.env_arr[line] = NULL;
}

void    cmd_env(t_all *all)
{
	int     i;

	i = 0;
	while (all->tline.env_arr[i])
	{
		printf("%s\n", all->tline.env_arr[i]);
		i++;
	}
}