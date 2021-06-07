#include "../minishell.h"

void	copy_env(t_all *all)
{
	int     i;
	int		j;
	
	j = 0;
	i = 0;
	while (all->tline.env_arr[j])
		j++;
	if (all->tline.export_arr != NULL)   // воможная утечка пофиксена? -30 leaks
	{
		while (all->tline.export_arr[i])
			free (all->tline.export_arr[i++]);
		free (all->tline.export_arr);
	}
	i = 0;
	all->tline.export_arr = (char **)malloc(sizeof(char *) * (j + 1));
	all->tline.export_arr[j] = NULL;
	while (all->tline.env_arr[i])
	{
		all->tline.export_arr[i] = ft_strdup(all->tline.env_arr[i]);
		i++;
	}
}

void    sort_env(t_all *all)
{
	int     j;
	int 	sort;
	char 	*tmp;

	sort = 0;
	while (!sort)
	{
		sort = 1;
		j = 0;
		while (all->tline.export_arr[j + 1] != NULL)
		{
			if (ft_strcmp(all->tline.export_arr[j], all->tline.export_arr[j + 1]) > 0)
			{
				tmp = all->tline.export_arr[j];
				all->tline.export_arr[j] = all->tline.export_arr[j + 1];
				all->tline.export_arr[j + 1] = tmp;
				sort = 0;
				break ;
			}
			j++;
		}
	}
}

int		find_equal_sign(t_all *all, char *line)
{
	int		j;
	int		cmp;

	j = ft_strchr_int(line, '=');
	cmp = ft_strlen(line) - 1;
	if (j == 0)
	{
		all->tline.equal_sign = 0;
		j = ft_strlen(line);
	}
	else if (j == cmp)
		all->tline.equal_sign = 1;
	return (j);
}

int		find_env_equal(t_all *all, char *line)
{
	int		j;
	int		cmp;

	j = ft_strchr_int(line, '=');
	cmp = ft_strlen(line) - 1;
	if (j == 0)
		j = ft_strlen(line);
	return (j);
}

char	*add_quotes(t_all *all, char *line)
{
	char	*tmp;
	int 	len;

	if (all->tline.equal_sign == 1)
		len = ft_strlen(line) + 3;
	else 
	if (all->tline.equal_sign == 0)
		len = ft_strlen(line) + 4;
	tmp = malloc(sizeof(len));
	if (all->tline.equal_sign == 1)
		tmp = ft_strjoin(line, "''");
	else if (all->tline.equal_sign == 0)
		tmp = ft_strjoin(line, "=''");
	tmp[len] = '\0';
	return (tmp);
}

int		check_val(t_all *all, char *line, int k)
{
	char	*tmp;
	char	*env_tmp;
	char	*str_w_quotes;
	int		i;
	int		j;

	i = 0;
	all->tline.equal_sign = -1;
	j = find_equal_sign(all, line);
	tmp = ft_substr(line, 0, j);
	while (all->tline.env_arr[i])
	{
		j = find_env_equal(all, all->tline.env_arr[i]);
		env_tmp = ft_substr(all->tline.env_arr[i], 0, j);
		if (strcmp(env_tmp, tmp) == 0)
		{
			if (all->tline.equal_sign == 0 || all->tline.equal_sign == 1)
				all->tline.env_arr[i] = add_quotes(all, line);
			else
			{
				all->tline.env_arr[i] = ft_realloc(all->tline.env_arr[i], ft_strlen(line));
				ft_strcpy(all->tline.env_arr[i], line);
			}
			return (1);
		}
		free (env_tmp);
		i++;
	}
	free (tmp);
	return (0);
}


void    cmd_export(t_all *all, int k)
{
	int 	i;
	int		j;
    int 	arr_len;
	char	*tmp;
	
	i = 0;
	j = 0;
	arr_len = len(all->tline.export_arr);
	while (all->cmd[k].arg[j])
	{
		if (!check_val(all, all->cmd[k].arg[j], k))
		{
			// printf("this is num of = ----- %d\n", all->tline.equal_sign);
			if (all->tline.equal_sign == 0 || all->tline.equal_sign == 1)
			{
				tmp = add_quotes(all, all->cmd[k].arg[j]);
				// printf("if strcmp != 0 export tmp = %s\n", tmp);
				if (!check_val(all, all->cmd[k].arg[j], k))
					add_new_env_param(all, tmp);
			}
			else
				add_new_env_param(all, all->cmd[k].arg[j]);
		}
		j++;
	}
	copy_env(all);
	sort_env(all);
	if (!all->cmd[k].arg[0])
	{
		while (all->tline.export_arr[i])
		{
		    printf("[%d] = declare -x %s\n", i, all->tline.export_arr[i]); //убрать d
			i++;
		}
	}
}