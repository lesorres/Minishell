#include "../minishell.h"

void	get_envp(t_all *all, char **envp)
{
	int	line;

	all->tline.env_line_num = 0;
	line = 0;
	while (envp[all->tline.env_line_num])
		all->tline.env_line_num++;
	// all->tline.env_arr = (char **)malloc(sizeof(char *)
		// * (all->tline.env_line_num + 1));
	all->tline.env_arr = ft_calloc((all->tline.env_line_num + 1), //leak
			sizeof(char *));
	while (line < all->tline.env_line_num)
	{
		all->tline.env_arr[line] = ft_strdup(envp[line]); //leak
		line++;
	}
	// all->tline.env_arr[line] = NULL;
	check_shlvl(all, all->tline.env_arr);
	write(1, "333\n", 4);  // debug
//	while (1){}  // debug
	split_path(all);
}

void	cmd_env(t_all *all, int k)
{
	int	i;

	i = 0;
	if (all->cmd[k].arg[1])
	{
		printf("%s: %s: %s\n", all->cmd[k].arg[0], all->cmd[k].arg[1],
			"No such file or directory");
		status = 127;
	}
	else
	{
		while (all->tline.env_arr[i])
		{
			printf("%s\n", all->tline.env_arr[i]);
			i++;
		}
		status = 0;
	}
}
