#include "../minishell.h"

void	change_shlvl(t_all *all, int i)
{
	char	*value;
	int		num;
	char	*tmp;
	char	*num_ch;

	num = ft_strlen(all->tline.env_arr[i]) - 6;
	value = ft_substr(all->tline.env_arr[i], 6, num);
	if (!isdigit_line(value))
		num = ft_atoi(value) + 1;
	else
		num = 1;
	num_ch = ft_itoa(num);
	tmp = ft_strjoin("SHLVL=", num_ch);
	free (all->tline.env_arr[i]);
	free(num_ch);
	free(value);
	all->tline.env_arr[i] = tmp;
}

void	check_shlvl(t_all *all)
{
	int		i;

	i = 0;
	while (all->tline.env_arr[i] && ft_strnstr(all->tline.env_arr[i],
			"SHLVL=", 6) == NULL)
		i++;
	if (find_var_in_arr(all->tline.env_arr, "SHLVL=") == -1
		&& all->tline.env_arr[i] == NULL)
	{
		add_new_env_param(all, "SHLVL=1");
		all->tline.first_shlvl = 1;
	}
	else if (all->tline.env_arr[i])
		change_shlvl(all, i);
}

void	get_envp(t_all *all, char **envp)
{
	int	line;

	all->tline.env_line_num = 0;
	line = 0;
	while (envp[all->tline.env_line_num])
		all->tline.env_line_num++;
	all->tline.env_arr = ft_calloc((all->tline.env_line_num + 1),
			sizeof(char *));
	while (line < all->tline.env_line_num)
	{
		all->tline.env_arr[line] = ft_strdup(envp[line]);
		line++;
	}
	check_shlvl(all);
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
		g_status = 127;
	}
	else
	{
		while (all->tline.env_arr[i])
		{
			printf("%s\n", all->tline.env_arr[i]);
			i++;
		}
		g_status = 0;
	}
}
