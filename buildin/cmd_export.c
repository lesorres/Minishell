#include "../minishell.h"

void	add_env_val(t_all *all, int i, char *line)
{
	if (all->tline.equal_sign == 0)
	{
		free(all->tline.env_arr[i]);
		all->tline.env_arr[i] = add_quotes(all, line);
	}
	else
	{
		all->tline.env_arr[i] = ft_realloc(all->tline.env_arr[i],
				ft_strlen(line));
		ft_strcpy(all->tline.env_arr[i], line);
	}
}

int	check_valid_id(char *cmd, char *line)
{
	int	i;

	i = 1;
	if (!ft_isalpha(line[0]) && line[0] != '_' && line[0] != '\''
		&& line[0] != '\"')
	{
		printf("minishell: %s: %s: %s\n", cmd, line, EXP_NOT_VAL);
		status = 1;
		return (1);
	}
	while (line[i])
	{
		if (ft_isalpha(line[i]) || ft_isdigit(line[i]) || line[i] == '_'
			|| line[0] != '\'' || line[0] != '\"')
			status = 0;
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

int	check_val(t_all *all, char *line, int k)
{
	char	*tmp;
	char	*env_tmp;
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
		if (ft_strcmp(env_tmp, tmp) == 0)
		{
			add_env_val(all, i, line);
			free (env_tmp);
			free (tmp);
			return (1);
		}
		free (env_tmp);
		i++;
	}
	free (tmp);
	return (0);
}

void	export_check_cycle(t_all *all, int k, int j)
{
	char	*tmp;

	while (all->cmd[k].arg[j])
	{
		if (!check_val(all, all->cmd[k].arg[j], k))
		{
			if (all->tline.equal_sign == 0)
			{
				if (!check_val(all, all->cmd[k].arg[j], k)
					&& !check_valid_id(all->cmd[k].arg[0], all->cmd[k].arg[j]))
				{
					tmp = add_quotes(all, all->cmd[k].arg[j]);
					add_new_env_param(all, tmp);
					status = 0;
					free (tmp);
				}
			}
			else if (!check_valid_id(all->cmd[k].arg[0], all->cmd[k].arg[j]))
			{
				add_new_env_param(all, all->cmd[k].arg[j]);
				status = 0;
			}
		}
		j++;
	}
}

void	cmd_export(t_all *all, int k)
{
	int		i;
	int		arr_len;
	int		j;

	j = 1;
	i = 0;
	arr_len = len(all->tline.export_arr);
	export_check_cycle(all, k, j);
	copy_env(all);
	sort_env(all);
	if (!ft_strncmp(all->cmd[all->cmd_i].arg[j], "PATH", 4)
			&& find_var_in_arr(all->tline.env_arr, "PATH") != -1)
		split_path(all);
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
