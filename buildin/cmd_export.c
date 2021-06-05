#include "../minishell.h"

void	copy_env(t_all *all)
{
	int     i;
	int		j;
	
	j = 0;
	i = 0;
	while (all->tline.env_arr[j])
		j++;
	all->tline.export_arr = (char **)malloc(sizeof(char *) * (j + 1)); //возможна утечка
	all->tline.export_arr[j] = NULL;
	while (all->tline.env_arr[i])
	{
		all->tline.export_arr[i] = ft_strdup(all->tline.env_arr[i]);
		i++;
	}
	// all->tline.export_arr[i] = NULL;
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
			if (ft_strncmp(all->tline.export_arr[j], all->tline.export_arr[j + 1]) > 0)
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

// int		check_env(t_all *all, char *line, int k)
// {
// 	int 	i;
// 	int		j;
// 	int		dif;

// 	i = 0;
// 	char	*env_tmp;
// 	while (all->tline.env_arr[i])
// 	{
// 		j = ft_strchr_int(all->tline.env_arr[i], '=');
// 		if (j == 0)
// 			j = ft_strlen(all->tline.env_arr[i]);
// 		env_tmp = ft_substr(all->tline.env_arr[i], 0, j);
// 		if (strcmp(env_tmp, all->tline.replaced_str) == 0)
// 		{
// 			all->tline.env_arr[i] = ft_realloc(all->tline.env_arr[i], ft_strlen(line));
// 			ft_strcpy(all->tline.env_arr[i], line);
// 			free (env_tmp);
// 			return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

int		find_equal_sign(t_all *all, char *line)
{
	int		j;
	int		cmp;

	j = ft_strchr_int(line, '=');
	// printf("first j ----------- %d\n", j);
	cmp = ft_strlen(line) - 1;
	// printf("cmp ------ %d\n", cmp);
	if (j == cmp)
	{
		all->tline.equal_sign = 0;
		// printf("equal sing # %d\n", j);
	}
	if (j == 0)
	{
		j = ft_strlen(line);
	}
	return (j);
}

int		check_val(t_all *all, char *line, int k)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	all->tline.equal_sign = -1;
	j = find_equal_sign(all, line);
	// printf("this is num of = ----- %d\n\n\n", all->tline.equal_sign);
	tmp = ft_substr(line, 0, j);
	all->tline.replaced_str = malloc(sizeof(ft_strlen(tmp)));
	all->tline.replaced_str = tmp;
	char	*env_tmp;
	while (all->tline.env_arr[i])
	{
		j = find_equal_sign(all, all->tline.env_arr[i]);
		env_tmp = ft_substr(all->tline.env_arr[i], 0, j);
		if (strcmp(env_tmp, all->tline.replaced_str) == 0)
		{
			all->tline.env_arr[i] = ft_realloc(all->tline.env_arr[i], ft_strlen(line));
			ft_strcpy(all->tline.env_arr[i], line);
			free (env_tmp);
			return (1);
		}
		i++;
	}
	return (0);
}

char	*add_quotes(t_all *all, char *line)
{
	char	*tmp;
	int 	len;

	len = ft_strlen(line) + 3;
	tmp = malloc(sizeof(len));
	tmp = ft_strjoin(line, "''");
	tmp[len] = '\0';
	// printf("this is tmp with quotes ----- %s\n", tmp);
	return (tmp);
}

void    cmd_export(t_all *all, int k)
{
	int i;
	int	j;
    int arr_len;
	char	*tmp;
	
	i = 0;
	j = 0;
	arr_len = len(all->tline.export_arr);
	while (all->cmd[k].arg[j])
	{
		if (!check_val(all, all->cmd[k].arg[j], k))      // проверять есть ли такая переменная окружения в массиве, если да - заменять значение
		{
			// printf("this is num of = ----- %d\n", all->tline.equal_sign);
			if (all->tline.equal_sign == 0)
			{
				tmp = add_quotes(all, all->cmd[k].arg[j]);
				add_new_env_param(all, tmp);
			}
			else
				add_new_env_param(all, all->cmd[k].arg[j]);
		}
		j++;
	}
	arr_len = len(all->tline.export_arr);
	copy_env(all);
	sort_env(all);
	if (!all->cmd[k].arg[0])
	{
		while (all->tline.export_arr[i])
		{
		    printf("declare -x %s\n", all->tline.export_arr[i]);
			i++;
		}
	}
}