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

int    cmd_unset(t_all *all, int k)
{
    int 	i;
	int		j;
	int		n;
	char	*tmp;

	n = 0;
    if (!all->cmd[k].arg[0])
        return (0);
    else
    {
        while (all->cmd[k].arg[n])
        {
    		i = 0;
			while (all->tline.env_arr[i])
			{
				j = find_env_equal(all, all->tline.env_arr[i]);
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