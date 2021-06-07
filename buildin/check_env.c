// void	check_env(t_all *all, char *line)
// {
// 	int 	i;
// 	int		j;
// 	int		dif;
// 	char	*env_tmp;

// 	i = 0;
// 	while (all->tline.env_arr[i])
// 	{
// 		j = ft_strchr_int(line, '=');
// 		printf("%d\n", j);
// 		env_tmp = ft_substr(all->tline.env_arr[i], 0, j);
// 		printf("\n\nenv_tmp ------ |%s|\n", env_tmp);
// 		// if (ft_strcmp(all->tline.env_arr[i], all->tline.replaced_str) == 0)
// 		i++;
// 	}
// }

// void	check_val(t_all *all, char *line)
// {
// 	char	*tmp;
// 	int		i;
// 	int		j;
// 	int		len;

// 	i = 0;
// 	j = ft_strchr_int(line, '=');
// 	tmp = ft_substr(line, 0, j);
// 	len  = ft_strlen(line) - j;
// 	all->tline.replaced_val = malloc(sizeof(len));
// 	all->tline.replaced_val = ft_substr(line, j, len);
// 	all->tline.replaced_str = malloc(sizeof(ft_strlen(tmp)));
// 	all->tline.replaced_str = tmp;
// 	printf("\n\ntmp = |%s|\n", all->tline.replaced_str);
// 	printf("\n\ntmp = |%s|\n", all->tline.replaced_val);
// 	check_env(all, line);
// }

// int		find_env_equal(t_all *all, char *line)
// {
// 	int		j;
// 	int		cmp;

// 	j = ft_strchr_int(line, '=');
// 	cmp = ft_strlen(line) - 1;
// 	if (j == 0)
// 		j = ft_strlen(line);
// 	return (j);
// }
