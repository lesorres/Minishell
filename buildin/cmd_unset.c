#include "../minishell.h"

void	del_env_line(t_all *all, int i)
{
	char	**new_arr;
	int		j;

	j = 0;
	free(all->tline.env_arr[i]);
	while (all->tline.env_arr[i + 1])
	{
		all->tline.env_arr[i] = all->tline.env_arr[i + 1];
		i++;
	}
	all->tline.env_arr[i] = NULL;
}

void	check_cycle(t_all *all, int k)
{
	int		i;
	int		j;
	int		n;
	char	*tmp;

	n = 1;
	while (all->cmd[k].arg[n])
	{
		i = 0;
		if (check_valid_id(all->cmd[k].arg[0], all->cmd[k].arg[n]))
			return ;
		else
		{
			while (all->tline.env_arr[i])
			{
				j = find_env_equal(all->tline.env_arr[i]);
				tmp = ft_substr(all->tline.env_arr[i], 0, j);
				if (ft_strcmp(tmp, all->cmd[k].arg[n]) == 0)
					del_env_line(all, i);
				i++;
				free (tmp);
			}
			n++;
		}
	}
}

int	cmd_unset(t_all *all, int k)
{
	int		i;
	int		n;

	n = 1;
	if (!all->cmd[k].arg[1])
		return (0);
	else
	{
		if (!ft_strncmp(all->cmd[k].arg[n], "PATH", 4))
			__free_arr(all->path_arr);
		check_cycle(all, k);
	}
	return (0);
}
