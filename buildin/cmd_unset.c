#include "../minishell.h"

void    del_env_line(t_all *all, int i)
{
    char    **new_arr;
    int     j;

	j = 0;
	free(all->tline.env_arr[i]);
	while (all->tline.env_arr[i + 1])
	{
		all->tline.env_arr[i] = all->tline.env_arr[i + 1];
		i++;
	}
	all->tline.env_arr[i] = NULL;
}

void	free_path_arr(t_all *all)
{
	int		i;

	i = 0;
	while (all->path_arr[i])
	{
		free(all->path_arr[i]);
		i++;
	}
	free (all->path_arr);
}

int    cmd_unset(t_all *all, int k)
{
    int 	i;
	int		j;
	int		n;
	char	*tmp;

	n = 1;
    if (!all->cmd[k].arg[1])
        return (0);
    else
    {
		if (!ft_strncmp(all->cmd[k].arg[n], "PATH", 4))
			free_path_arr(all);
        while (all->cmd[k].arg[n])
        {
    		i = 0;
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
    return(1);
}