#include "../minishell.h"

void    get_envp(t_all *all, char **envp)
{
	int     line;
	
	all->tline.env_line_num = 0;
	line = 0;
	while (envp[all->tline.env_line_num])
		all->tline.env_line_num++;
	all->tline.env_arr = (char **)malloc(sizeof(char *) * (all->tline.env_line_num + 1));
	while (line < all->tline.env_line_num)
	{
		all->tline.env_arr[line] = ft_strdup(envp[line]);
		line++;
	}
	all->tline.env_arr[line] = NULL;
	// check_shlvl(all, all->tline.env_arr);
}

void    cmd_env(t_all *all, int k)
{
	int     i;

	i = 0;
	while (all->tline.env_arr[i])
	{
		printf("i = %d env = %s\n", i, all->tline.env_arr[i]);
		i++;
	}
}