#include "../minishell.h"

void	copy_env(t_all *all)
{
	int     i;
	int		j;
	
	j = 0;
	i = 0;
	while (all->tline.env_arr[j])
		j++;
	if (all->tline.export_arr != NULL)
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
	if (j == -1)  //j ==0
	{
		all->tline.equal_sign = 0;
		j = ft_strlen(line);
	}
	else if (j == cmp)
		all->tline.equal_sign = 1;
	return (j);
}

int		find_env_equal(char *line)
{
	int		j;
	int		cmp;

	j = ft_strchr_int(line, '=');
	cmp = ft_strlen(line) - 1;
	if (j == -1)
		j = ft_strlen(line);
	return (j);
}

char	*add_quotes(t_all *all, char *line)
{
	char	*tmp;
	int 	len;

	// if (all->tline.equal_sign == 1)
	// 	len = ft_strlen(line) + 3;
	// else 
	if (all->tline.equal_sign == 0)
		len = ft_strlen(line) + 3;
	tmp = malloc(sizeof(len));
	// if (all->tline.equal_sign == 1)
	// 	tmp = ft_strjoin(line, "''");
	// else 
	if (all->tline.equal_sign == 0)
		tmp = ft_strjoin(line, "=");
	tmp[len] = '\0';
	return (tmp);
}

void	add_env_val(t_all *all, int i, char *line)
{
	if (all->tline.equal_sign == 0) // || all->tline.equal_sign == 1)  //
		all->tline.env_arr[i] = add_quotes(all, line);
	else
	{
		all->tline.env_arr[i] = ft_realloc(all->tline.env_arr[i], ft_strlen(line));
		ft_strcpy(all->tline.env_arr[i], line);
	}
}

int	check_valid_id(char *cmd, char *line)
{
	int	i;

	i = 1;
	if (!ft_isalpha(line[0]) && line[0] != '_' && line[0] != '\'' && line[0] != '\"') //сделать доп проверку кавычек 
	{
		printf("minishell: %s: %s: %s\n", cmd, line, EXP_NOT_VAL);
		status = 1;
		return (1);
	}
	while (line[i])
	{
		if (ft_isalpha(line[i]) || ft_isdigit(line[i]) || line[i] == '_' || line[0] != '\'' || line[0] != '\"')
		{
			status = 0;
			return (0);
		}
		else
		{
			printf("minishell: %s: %s: %s\n", cmd, line, EXP_NOT_VAL);
			status = 1;
			return (1);
		}
		i++;
	}
	return (0);
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
		j = find_env_equal(all->tline.env_arr[i]);
		env_tmp = ft_substr(all->tline.env_arr[i], 0, j);
		if (strcmp(env_tmp, tmp) == 0)
		{
			add_env_val(all, i, line);
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
	j = 1;
	arr_len = len(all->tline.export_arr);
	while (all->cmd[k].arg[j])
	{
		// check_valid_id(all->cmd[k].arg[0], all->cmd[k].arg[j]);
		// if (check_valid_id(all->cmd[k].arg[0], all->cmd[k].arg[j]))
			// return ;
		// else if (!check_val(all, all->cmd[k].arg[j], k))
		if (!check_val(all, all->cmd[k].arg[j], k))
		{
			if (all->tline.equal_sign == 0) // || all->tline.equal_sign == 1)
			{
				tmp = add_quotes(all, all->cmd[k].arg[j]);
				if (!check_val(all, all->cmd[k].arg[j], k) && !check_valid_id(all->cmd[k].arg[0], all->cmd[k].arg[j]))   //without && !check...
				{
					add_new_env_param(all, tmp);
					status = 0;
				}
			}
			else if (!check_valid_id(all->cmd[k].arg[0], all->cmd[k].arg[j]))   //else
			{
				add_new_env_param(all, all->cmd[k].arg[j]);
				status = 0;
			}
		}
		j++;
	}
	copy_env(all);
	sort_env(all);
	if (!all->cmd[k].arg[1])
	{
		while (all->tline.export_arr[i])
		{
		    printf("declare -x %s\n", all->tline.export_arr[i]);
			i++;
		}
		status = 0;
	}
}