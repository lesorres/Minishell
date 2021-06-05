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

int		check_env(t_all *all, char *line, int k)
{
	int 	i;
	int		j;
	int		dif;
	char	*env_tmp;
	int		num;

	i = 0;
	while (all->tline.env_arr[i])
	{
		j = ft_strchr_int(all->tline.env_arr[i], '=');
		if (j == 0)
			j = ft_strlen(all->tline.env_arr[i]);
		env_tmp = ft_substr(all->tline.env_arr[i], 0, j);
			// printf("[i] ----- %d ft_strncmp ===== %d\n", i, strcmp(env_tmp, all->tline.replaced_str));
			num = ft_strlen(all->tline.replaced_str);
			// printf("replaced str -------= |%s|\n", all->tline.replaced_str);
			// printf("env_arr str -------= |%s|\n", all->tline.env_arr[i]);
			// printf("lelem of replaced string ---- %d\n", (int)all->tline.replaced_str[num - 1]);
			// printf("last elem of replaced string ---- %d\n", (int)all->tline.replaced_str[num]);
		if (strcmp(env_tmp, all->tline.replaced_str) == 0)
		{
			// free (all->tline.env_arr[i]);
			// printf("\nenv_tmp ------ |%s|\n", env_tmp);
			all->tline.env_arr[i] = ft_realloc(all->tline.env_arr[i], ft_strlen(line));
			// all->tline.env_arr[i] = malloc(sizeof(ft_strlen(line)));
			ft_strcpy(all->tline.env_arr[i], line);
			free (env_tmp);
			return (1);
		}
			num = ft_strlen(all->tline.env_arr[i]);
			// printf("elem env+arr ---- %d\n", (int)all->tline.env_arr[i][num - 1]);
			// printf("last elem env+arr ---- %d\n\n", (int)all->tline.env_arr[i][num]);
		i++;
	}
	return (0);
		// printf("\n\nreplaced str -------= |%s|\n", all->tline.replaced_str);
		// printf("\nenv_tmp ------ |%s|\n", env_tmp);
}

int		check_val(t_all *all, char *line, int k)
{
	char	*tmp;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = ft_strchr_int(line, '=');
	if (j == 0)
		j = ft_strlen(line);
	tmp = ft_substr(line, 0, j);
	len  = ft_strlen(line) - (j + 1);
	all->tline.replaced_val = malloc(sizeof(len - 1));
	all->tline.replaced_val = ft_substr(line, (j + 1), len);
	all->tline.replaced_str = malloc(sizeof(ft_strlen(tmp)));
	all->tline.replaced_str = tmp;
	// int num = ft_strlen(all->tline.replaced_str);
	// printf("last elem of replaced string ---- %d\n", (int)all->tline.replaced_str[num]);
	// while (all->tline.env_arr[i])
	// {
	// 	j = ft_strchr_int(all->tline.env_arr[i], '=');
	// 	tmp = ft_substr(all->tline.env_arr[i], 0, j);
	// 	if (strcmp(tmp, all->tline.replaced_str) == 0)
	// 	{
	// 		// free (all->tline.env_arr[i]);
	// 		all->tline.env_arr[i] = ft_realloc(all->tline.env_arr[i], ft_strlen(line));
	// 		// all->tline.env_arr[i] = ft_realloc(sizeof(ft_strlen(line)));
	// 		ft_strcpy(all->tline.env_arr[i], line);
	// 		free (tmp);
	// 		return (1);
	// 	}
	// 	i++;
	// }
	// return (0);
	printf("\n\ntmp = |%s|\n", all->tline.replaced_str);
	printf("\n\nthis isn't tmp = |%s|\n", all->tline.replaced_val);
	if (check_env(all, line, k) == 1)
		return (1);
	return (0);
}

void    cmd_export(t_all *all, int k)
{
	int i;
	int	j;
    int arr_len;
	
	i = 0;
	j = 0;
	arr_len = len(all->tline.export_arr);
	while (all->cmd[k].arg[j])
	{
		printf("args[%d] ---- |%s|\n", j, all->cmd[k].arg[j]);
		if (!check_val(all, all->cmd[k].arg[j], k))      // проверять есть ли такая переменная окружения в массиве, если да - заменять значение
			add_new_env_param(all, all->cmd[k].arg[j]);
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