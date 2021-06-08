#include "../minishell.h"

int	error_handler(char *arg1, char *arg2, char *err)
{
	write(1, "minishell: ", PROMPT);
	printf("%s: %s: %s\n", arg1, arg2, err);
	return(1);
}


	// j = ft_strchr_int(line, '=');
	// cmp = ft_strlen(line) - 1;
	// if (j == 0)
	// 	j = ft_strlen(line);
	// return (j);
	// j = find_equal_sign(all, line);
	// tmp = ft_substr(line, 0, j);

void	srch_str_in_arr(t_all *all, char *path)
{
	int		i;

	i = 0;
	while (all->tline.env_arr[i])
	{
		if (!ft_strncmp(all->tline.env_arr[i], "PWD=", 4))
			break ;
		i++;
	}
	all->tline.env_arr[i] = ft_realloc(all->tline.env_arr[i], ft_strlen(path));
	ft_strcpy(all->tline.env_arr[i], path);
}

// char	*change_line(t_all *all, char *str1, char *str2, char *added_line)
// {
// 	int		i;
// 	int		size;
// 	char	*tmp;

// 	i = 0;
// 	size = ft_strlen(str2);
// 	if (ft_strncmp(str1, str2, size))
// 		add_new_env_param(all, added_line);
// 	else
// 	{
// 		// tmp = ft_strdup(str1);
// 		str1 = ft_realloc(str1, ft_strlen(added_line));
// 		ft_strcpy(str1, added_line);
// 	}
// 	printf("change line - str1 %s\n", str1);
// 	// free (tmp);
// 	return (str1);
// }

void	add_oldpwd(t_all *all, char *oldpwd)
{
	int		i;

	i = 0;
	while (ft_strncmp(all->tline.env_arr[i], "OLDPWD=", 8) != 0)
		i++;
	printf("oldpwd --- %s\n", all->tline.env_arr[i]);
	if (ft_strncmp(all->tline.env_arr[i], "OLDPWD=", 8) == 0)
	{
		printf("before oldpwd --- %s\n", all->tline.env_arr[i]);
		all->tline.env_arr[i] = ft_realloc(all->tline.env_arr[i], ft_strlen(all->builds.oldpwd));
		ft_strcpy(all->tline.env_arr[i], all->builds.oldpwd);
		printf("after oldpwd --- %s\n", all->tline.env_arr[i]);
			// change_line(all, all->tline.env_arr[i], "OLDPWD=", all->builds.oldpwd);
			// add_new_env_param(all, all->builds.oldpwd);
			// printf("add new param ---- %s\n", all->tline.env_arr[i]);
			// break ;
	}
	else
		add_new_env_param(all, all->builds.oldpwd);
		// 	all->tline.env_arr[i] = ft_realloc(all->tline.env_arr[i], ft_strlen(all->builds.oldpwd));
		// 	ft_strcpy(all->tline.env_arr[i], all->builds.oldpwd);
		// 	printf("new env_arr ---- %s\n", all->tline.env_arr[i]);
		// 	return (0);
		// i++;
}

int cmd_cd(t_all *all, char **envp, int k)
{
	char    *path;
	char    *tmp_path;
	char	*tmp;
	char	*pwd;
	int		error_num;
	int		i;

	path = malloc(PATH_LEN + 1);
	all->builds.oldpwd = getcwd(path, PATH_LEN);
	// printf("oldpwd ---- %s\n", all->builds.oldpwd);
	if (all->cmd[k].arg[0] && ft_strcmp(all->cmd[k].arg[0], "."))
	{
		if (chdir(all->cmd[k].arg[0]) == -1)
			error_handler(all->cmd[k].name, all->cmd[k].arg[0], strerror(errno));
		else
		{
			i = 0;
			tmp = getcwd(tmp, PATH_LEN);
			pwd = ft_strjoin("PWD=", tmp);
			// printf("tmp  if new PWD --- %s\n", tmp);
			while (ft_strncmp(all->tline.env_arr[i], "PWD=", 4) != 0)
				i++;
			// printf("env_arr[i] before ft_cpy ---- %s\n", all->tline.env_arr[i]);
			all->tline.env_arr[i] = ft_realloc(all->tline.env_arr[i], ft_strlen(pwd));
			ft_strcpy(all->tline.env_arr[i], pwd);
			// printf("env_arr[i] after ft_cpy ---- %s\n", all->tline.env_arr[i]);
		}
	}
	else if (!all->cmd[k].arg[0] && ft_strcmp(all->cmd[k].arg[0], "."))
	{
		tmp_path = getenv("HOME");
		chdir(tmp_path);
		printf("path --- %s\n", tmp_path);
	}                                        // обработать добавление OLDPWD в массив env и export
	// add_oldpwd(all, all->builds.oldpwd);
	i = 0;
	while (all->tline.env_arr[i])
	{
		// printf("before oldpwd --- %s\n", all->tline.env_arr[i]);
		if (ft_strncmp(all->tline.env_arr[i], "OLDPWD=", 8) != 0)
			i++;
		else if (ft_strncmp(all->tline.env_arr[i], "OLDPWD=", 8) == 0)
		{
			printf("before oldpwd --- %s\n", all->tline.env_arr[i]);
			all->tline.env_arr[i] = ft_realloc(all->tline.env_arr[i], ft_strlen(all->builds.oldpwd));
			ft_strcpy(all->tline.env_arr[i], all->builds.oldpwd);
			printf("after oldpwd --- %s\n", all->tline.env_arr[i]);
			break ;
		}
	}
		if (ft_strncmp(all->tline.env_arr[i], "OLDPWD=", 8) != 0)
			add_new_env_param(all, all->builds.oldpwd);
	// printf("oldpwd --- %s\n", all->tline.env_arr[i]);
	// if (ft_strncmp(all->tline.env_arr[i], "OLDPWD=", 8) == 0)
	// {
	// 	printf("before oldpwd --- %s\n", all->tline.env_arr[i]);
	// 	all->tline.env_arr[i] = ft_realloc(all->tline.env_arr[i], ft_strlen(all->builds.oldpwd));
	// 	ft_strcpy(all->tline.env_arr[i], all->builds.oldpwd);
	// 	printf("after oldpwd --- %s\n", all->tline.env_arr[i]);
	// 		// change_line(all, all->tline.env_arr[i], "OLDPWD=", all->builds.oldpwd);
	// 		// add_new_env_param(all, all->builds.oldpwd);
	// 		// printf("add new param ---- %s\n", all->tline.env_arr[i]);
	// 		// break ;
	// }
	// else
	// 	add_new_env_param(all, all->builds.oldpwd);
	// while (all->tline.env_arr[i])
	// {
	// 	// printf("env_arr ---- %s\n", all->tline.env_arr[i]);
	// 	if (ft_strncmp(all->tline.env_arr[i], "OLDPWD", 8))
	// 	{
	// 		change_line(all, all->tline.env_arr[i], "OLDPWD", all->builds.oldpwd);
	// 		// add_new_env_param(all, all->builds.oldpwd);
	// 		// printf("add new param ---- %s\n", all->tline.env_arr[i]);
	// 		break ;
	// 	}
	// 	// else
	// 	// {
	// 	// 	all->tline.env_arr[i] = ft_realloc(all->tline.env_arr[i], ft_strlen(all->builds.oldpwd));
	// 	// 	ft_strcpy(all->tline.env_arr[i], all->builds.oldpwd);
	// 	// 	printf("new env_arr ---- %s\n", all->tline.env_arr[i]);
	// 	// 	return (0);
	// 	// }
	// 	i++;
	// }
	// free(path);
	return (0);
}