#include "minishell.h"

int	error_handler(char *arg1, char *arg2, int num)
{
	write(1, "minishell: ", PROMPT);
	if (num == 2)
		printf("%s: %s: %s\n", arg1, arg2, "No such file or directory");
	else if (num == 20)
		printf("%s: %s: %s\n", arg1, arg2, "Not a directory");
	return(1);
}

static int len(char **str)
{
    int	i;

	i = 0;
	while (str && str[i])
		i++;
    i += 1;
	return (i);
}

void    add_new_env_param(t_all *all, char *line)
{
	char	**new_arr;
	int		line_len;;


	line_len = len(all->tline.env_arr); // line = all->cmd[0].arg[1]
	printf("arr_len = %i\n", line_len);
	if(!(new_arr = calloc((line_len + 1), sizeof(char *))))
		printf("error");
	// new_arr[line_len] = NULL;
	new_arr[line_len] = line;
	int i = 0;
	while (i < line_len)
	{
		new_arr[i] = all->tline.env_arr[i];
		i++;
	}
	free(all->tline.env_arr);
	all->tline.env_arr = new_arr;
	line_len = len(all->tline.env_arr); // line = all->cmd[0].arg[1]
	printf("arr_len = %i\n", line_len);
	// free(new_arr);
	// int	k = 0;
	// while (all->tline.env_arr[k])
	// 	printf("add_new_env - %s\n", all->tline.env_arr[k++]);
}

int cmd_cd(t_all *all, char **envp)
{
	char    *path;
	char    *tmp_path;
	int		error_num;

	path = malloc(PATH_LEN + 1);
	all->builds.oldpwd = getcwd(path, PATH_LEN);
	if (all->cmd[0].arg[1] && ft_strncmp(all->cmd[0].arg[1], "."))
	{
		if (chdir(all->cmd[0].arg[1]) == -1)
		{
			error_num = errno;
			error_handler(all->cmd[0].arg[0], all->cmd[0].arg[1], error_num);
		}
	}
	else if (!all->cmd[0].arg[1] || !ft_strncmp(all->cmd[0].arg[1], "."))
	{
		tmp_path = getenv("HOME");
		chdir(tmp_path);
	}                                        // обработать добавление OLDPWD в массив env и export
	add_new_env_param(all, all->builds.oldpwd);
	free(path);
	return (0);
}

void cmd_echo(t_all *all, char **argv)
{
	int     i;
	int     j;
	
	i = 1;
	j = 0;
	while (!all->cmd[0].null && all->cmd[0].arg[i])          // аргументы echo в парсере должны обрабатываться как один
	{
		if (!ft_strncmp(all->cmd[0].arg[i], "-n"))
			i = 2;    
		write(1, all->cmd[0].arg[i], ft_strlen(all->cmd[j].arg[i]));
		if (strcmp(all->cmd[0].arg[1], "-n"))
			write(1, "\n", 1);
		i++;
	}
}


// int add_new_param(t_all *all, char ***input, char *line)
// {
//     char    **out;
//     int     i;
    
//     i = all->tline.env_line_num;
// 	printf("%d\n", i);
//     if(!(out = (char**)calloc((i + 1), sizeof(char*))))  //malloc
//         return(0);
//     out[i] = NULL;
//     out[--i] = line;
//     while (i--)
//         out[i] = (*input)[i];
//     free(*input);
//     *input = out;
// 	int	k = 0;
// 	while (input[k])
// 		printf("input = %s/n", *input[k++]);
//     return(1);
// }

void    cmd_pwd(t_all *all, char **envp)    // вроде работает все веерно???
{
	char    *path;
	char    *tmp;

	path = malloc(PATH_LEN + 1);
	tmp = getcwd(path, PATH_LEN);
	write(1, tmp, ft_strlen(tmp));
	write(1, "\n", 1);
	free(path);
}

void    sort_env(t_all *all)    //  неправильная сортировка + заполняет массив пустыми строками вместо переменных окружения
{
	int     i;
	int     j;
	char    *tmp_line;

	i = 0;
	while (i < all->tline.env_line_num - 1)
	{
		j = 0;
		// printf("env_arr[%d] - %s\n", i, all->tline.env_arr[i]);
		// printf("%d\n", ft_strncmp(all->tline.env_arr[i], all->tline.env_arr[i + 1]));
		while (j < all->tline.env_line_num - 2)
		{
			if (ft_strncmp(all->tline.export_arr[i], all->tline.export_arr[i + 1]) == -1)
			{
				tmp_line = malloc(sizeof(ft_strlen(all->tline.export_arr[i + 1])));
				tmp_line = all->tline.export_arr[i + 1];
				all->tline.export_arr[i + 1] = all->tline.export_arr[i];
				all->tline.export_arr[i] = tmp_line;
				free(tmp_line);
			}
			j++;
		}
		// printf("exp_arr[%d] - %s\n\n", i, all->tline.export_arr[i]);
		i++;
	}
		// printf("exp_arr = 26 [%d] - %d\n", i, all->tline.export_arr[26][0]);
}

int	is_print_line(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (0 <= str[i] && str[i] <= 127)
			i++;
		else
			return (1);
	}
	return (0);
}

void    get_envp(t_all *all, char **envp)  // ок
{
	int     line;
	
	all->tline.env_line_num = 0;
	line = 0;
	while (envp[all->tline.env_line_num])
		all->tline.env_line_num++;
	all->tline.env_arr = (char **)malloc(sizeof(char *) * (all->tline.env_line_num));
	while (line < all->tline.env_line_num)
	{
		all->tline.env_arr[line] = ft_strdup(envp[line]);
		line++;
	}
	all->tline.env_arr[line] = NULL;
	// int i = 0;
	// while (all->tline.env_arr[i])
	//     printf("%s\n", all->tline.env_arr[i++]);
}

void    cmd_env(t_all *all)
{
	int     i;

	i = 0;
	// get_envp(all, envp);
	// if (all->builds.export_new_arg == 1)
	// 	add_new_env_param(all, all->cmd[0].arg[1]);
	// printf("%d\n", (int)all->tline.env_arr[0]);
	// printf("%d\n", (int)all->tline.env_arr[1]);
	while (all->tline.env_arr[i])
	{
		printf("%s\n", all->tline.env_arr[i]);
		i++;
	}

}

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

void    cmd_export(t_all *all, char **envp)
{
	int i;
	
	i = 0;
	// printf("exp_arr[i] - %s\n", *all->tline.export_arr);
	int arr_len = len(all->tline.export_arr);
	// printf("arr_len1 = %i\n", arr_len);
	if (all->cmd[0].arg[1])   // проверять есть ли такая переменная окружения в массиве, если да - заменять значение
	{
		add_new_env_param(all, all->cmd[0].arg[1]);
		all->builds.export_new_arg = 1;
	}
	arr_len = len(all->tline.export_arr);
	// printf("arr_len2 = %i\n", arr_len);
	// while (all->tline.export_arr[i])
	// {
	//     printf("declare -x %s\n", all->tline.export_arr[i]);
	// 	i++;
	// }
	copy_env(all);
	// sort_env(all);
	i = 0;
	// while (all->tline.export_arr[i])
	// {
	//     printf("declare -x %s\n", all->tline.export_arr[i]);
	// 	i++;
	// }
}

int		exit_error(char *cmd, char *arg, char *error)
{
	printf("%s: %s: %s:\n", cmd, arg, error);
	return (0);
}

// void	cmd_exit(t_all *all, char **arg)
// {
// 	int	i;

// 	i = 2;
// 	if (all->cmd[0].arg[i])
// 	{
// 		if (ft_isalpha(all->cmd[0].arg[1]))
// 		{
// 			exit_error(all->cmd[0].arg[0], all->cmd[0].arg[1], "numeric argument required");
// 			exit (0);
// 		}
// 		else if (ft_isdigit(all->cmd[0].arg[1]))
// 		{
// 			if (all->cmd[0].arg[])
// 		}
// 			error_handler();
// 	}
// }

void    buildin_func(t_all *all, char **arg, char **envp)
{
	all->builds.export_new_arg = 0;
	get_envp(all, envp);
	if (!strcmp(all->cmd[0].arg[0], "cd"))
		cmd_cd(all, envp);
	else if (!strcmp(all->cmd[0].arg[0], "echo"))
		cmd_echo(all, arg);
	if (!strcmp(all->cmd[0].arg[0], "pwd"))
		cmd_pwd(all, envp);
	else if (!strcmp(all->cmd[0].arg[0], "export"))
	{
		cmd_export(all, envp);
	// else if (strcmp(all->cmd->arg[0], "unset "))
	//     cmd_unset(all, arg, envp);
	}
	else if (!strcmp(all->cmd[0].arg[0], "env"))
		cmd_env(all);
	// else if (strcmp(all->cmd->arg[0], "exit"))
	//     cmd_exit(all, arg);
}