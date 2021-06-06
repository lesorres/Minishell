#include "../minishell.h"


int		check(t_all *all, char *line, int k)
{
	char	*tmp;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = ft_strchr_int(line, '=');
	tmp = ft_substr(line, 0, j);
	len  = ft_strlen(line) - j;
	// all->tline.replaced_str = malloc(sizeof(ft_strlen(tmp)));
	// all->tline.replaced_str = tmp;
	while (all->tline.env_arr[i])
	{
		j = ft_strchr_int(all->tline.env_arr[i], '=');
		tmp = ft_substr(all->tline.env_arr[i], 0, j);
		// printf("ft_strncmp ===== %d\n", ft_strncmp(tmp, all->tline.replaced_str));
		if (ft_strncmp(tmp, all->tline.replaced_str) == 0)
		{
			free (all->tline.env_arr[i]);
			all->tline.env_arr[i] = malloc(sizeof(ft_strlen(line)));
			ft_strcpy(all->tline.env_arr[i], line);
			return (1);
		}
		i++;
	}
	return (0);
}

void    del_env_line(t_all *all, int i)
{
    char    **new_arr;
    int     j;

	j = 0;
	free(all->tline.env_arr[i]);
	printf("env[i] = %s\n", all->tline.env_arr[i]);
	while (all->tline.env_arr[i + 1])
	{
		all->tline.env_arr[i] = all->tline.env_arr[i + 1];
		i++;
	}
	all->tline.env_arr[i] = NULL;
}

int dl_l_line(char ***input)
{
    char    **out;
    int     i;
    
    i = len(*input);
    if(!(out = (char**)malloc(sizeof(char*) * (i + 1))))
        return(0);
    out[i] = NULL;
    free((*input)[i]);
    while (i--)
        out[i] = (*input)[i];
    free(*input);
    *input = out;
    return(1);
}

int    cmd_unset(t_all *all, int k)
{
    int 	i;
	int		j;
	int		n;
	char	*tmp;

    i = 0;
	n = 0;
    if (!all->cmd[k].arg[0])
        return (0);
    else
    {
        while (all->cmd[k].arg[n])
        {
			// printf("\n\nif [n] = %d, all->cmd[i].arg[n] --- %s\n\n", n, all->cmd[k].arg[n]);
			while (all->tline.env_arr[i])
			{
				j = find_env_equal(all, all->tline.env_arr[i]);
				tmp = ft_substr(all->tline.env_arr[i], 0, j);
				printf("if [i] = %d, tmp --- %s\n", i, tmp);
				if (ft_strncmp(tmp, all->cmd[k].arg[n]) == 0)
            		del_env_line(all, i);
				i++;
			}
			// printf("array str --- %s\n", all->tline.env_arr[i]);
        	n++;
        } 
		i = 0;
		while (all->tline.env_arr[i])
		{
		printf("[%d] env = %s\n", i, all->tline.env_arr[i]);
		i++;
		}
    }
    return(1);
}