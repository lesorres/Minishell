#include "minishell.h"

void cmd_echo(t_all *all, char **argv)
{
	int     i;
	int     j;
	
	i = 1;
	j = 0;
	while (!all->cmd[j].null && all->cmd[j].arg[i])
	{
		// while (argv[i][j])
		{
			if (!strcmp(all->cmd[j].arg[i], "-n"))
				i = 2;    
			write(1, all->cmd[j].arg[i], ft_strlen(all->cmd[j].arg[i]));
			if (strcmp(all->cmd[j].arg[i], "-n"))
				write(1, "\n", 1);
			i++;
		}
	}
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

int add_new_param(t_all *all, char ***input, char *line)
{
    char    **out;
    int     i;
    
    i = all->tline.env_line_num;
    if(!(out = (char**)calloc((i + 1), sizeof(char*))))  //malloc
        return(0);
    out[i] = NULL;
    out[--i] = line;
    while (i--)
        out[i] = (*input)[i];
    free(*input);
    *input = out;
    return(1);
}

void    add_new_env_param(t_all *all, char *line)
{
	char	**new_arr;
	int		line_len;;

	line_len = all->tline.env_line_num; // line = all->cmd[0].arg[1]
	if(!(new_arr = (char **)calloc((line_len + 1), sizeof(char*))))
		printf("error");
	new_arr[line_len] = NULL;
	new_arr[--line_len] = line;
	while (line_len--)
		new_arr[line_len] = all->tline.env_arr[line_len];
	free(all->tline.env_arr);
	all->tline.env_arr = new_arr;
}

int	error_handler(char *arg1, char *arg2, int num)
{
	if (num == 2)
		printf("%s: %s: %s\n", arg1, arg2, "No such file or directory");
	else if (num == 20)
		printf("%s: %s: %s\n", arg1, arg2, "Not a directory");
	return(1);
}

int cmd_cd(t_all *all, char **envp)
{
	int     dir;
	char    *path;
	char    *tmp_path;
	int		error_num;

	if (all->cmd[0].arg[1] && ft_strncmp(all->cmd[0].arg[1], "."))
	{
		dir = chdir(all->cmd[0].arg[1]);
		if (dir == -1)
		{
			// printf("%d\n", dir);
			error_num = errno;
			// printf("%d\n", error_num);
			if (error_num == 2)
				error_handler(all->cmd[0].arg[0], all->cmd[0].arg[1], error_num);
			// {
			// 	printf("%s: %s: %s\n", all->cmd[0].arg[0], all->cmd[0].arg[1], "No such file or directory");
			// 	return(1);
			// }
			else if (error_num == 20)
				error_handler(all->cmd[0].arg[0], all->cmd[0].arg[1], error_num);
			// {
			// 	printf("%s: %s: %s\n", all->cmd[0].arg[0], all->cmd[0].arg[1], "Not a directory");
			// 	return(1);
			// }
		}
	}
	else if (!all->cmd[0].arg[1] || !ft_strncmp(all->cmd[0].arg[1], "."))
	{
		tmp_path = getenv("HOME");
		chdir(tmp_path);
	}
	// printf("oldpwd - %s\n", all->builds->oldpwd);
	// path = malloc(PATH_LEN + 1);
	// all->builds->oldpwd = getcwd(path, PATH_LEN);
	// add_new_param(all, &all->tline.env_arr, all->builds->oldpwd);
	// free(path);
	return (0);
}

// int		ft_putstr(char *str)
// {
// 	int	i;
// 	int	ret;

// 	i = -1;
// 	ret = 0;
// 	while (str[++i])
// 		ret += write(1, &str[i], 1);
// 	return (ret);
// }

void    cmd_pwd(t_all *all, char **envp)
{
	char    *path;
	char    *tmp;

	path = malloc(PATH_LEN + 1);
	tmp = getcwd(path, PATH_LEN);
	write(1, tmp, ft_strlen(tmp));
	write(1, "\n", 1);
	free(path);
}

void    sort_env(t_all *all)
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

void    get_envp(t_all *all, char **envp)
{
	int     line;
	int     line_count;
	
	all->tline.env_line_num = 0;
	line = 0;
	while (envp[all->tline.env_line_num])
		all->tline.env_line_num++;
	line_count = all->tline.env_line_num;
	all->tline.env_arr = (char **)malloc(sizeof(char *) * (all->tline.env_line_num + 1));
	while (line_count)
	{
		if (ft_strncmp(envp[line], "\n") || ft_strncmp(envp[line], NULL))
			all->tline.env_arr[line] = ft_strdup(envp[line]);
		line++;
		line_count--;
	}
	all->tline.env_arr[all->tline.env_line_num + 1] = NULL;
	// int i = 0;
	// while (all->tline.env_arr[i])
	//     printf("%s\n", all->tline.env_arr[i++]);
}

void    cmd_env(t_all *all)
{
	int     i;

	i = 0;
	// get_envp(all, envp);
	// printf("%s\n", all->tline.env_arr[i]);
	while (all->tline.env_arr[i])
	{
		printf("i - %d |%s|\n", i, all->tline.env_arr[i]);
		i++;
	}
}

void	copy_env(t_all *all)
{
	int     line;
	int     line_count;
	
	all->tline.exp_line_num = 0;
	line = 0;
	while (all->tline.env_arr[all->tline.exp_line_num])
		all->tline.exp_line_num++;
	line_count = all->tline.exp_line_num;
	all->tline.export_arr = (char **)malloc(sizeof(char *) * (all->tline.exp_line_num));
	while (line_count)
	{
		if (ft_strncmp(all->tline.env_arr[line], "\n") || ft_strncmp(all->tline.env_arr[line], NULL))
			all->tline.export_arr[line] = ft_strdup(all->tline.env_arr[line]);
		line++;
		line_count--;
	}
	// all->tline.export_arr[all->tline.env_line_num + 1] = NULL;
}

void    cmd_export(t_all *all, char **envp)
{
	copy_env(all);
	// printf("exp_arr[i] - %s\n", *all->tline.export_arr);
	if (!all->cmd[0].arg[1])
	{
		sort_env(all);
		int i = 0;
		while (all->tline.export_arr[i])
		{
		    printf("i = %d |declare -x %s|\n", i, all->tline.export_arr[i]);
			i++;
		}
	}
	else
		add_new_param(all, &all->tline.env_arr, all->cmd[0].arg[1]);
}

void    buildin_func(t_all *all, char **arg, char **envp)
{
	get_envp(all, envp);
	if (!strcmp(all->cmd[0].arg[0], "cd"))
		cmd_cd(all, envp);
	else if (!strcmp(all->cmd[0].arg[0], "echo"))
		cmd_echo(all, arg);
	if (!strcmp(all->cmd[0].arg[0], "pwd"))
		cmd_pwd(all, envp);
	else if (!strcmp(all->cmd->arg[0], "export"))
		cmd_export(all, envp);
	// else if (strcmp(all->cmd->arg[0], "unset "))
	//     cmd_unset(all, arg, envp);
	else if (!strcmp(all->cmd[0].arg[0], "env"))
		cmd_env(all);
	// else if (strcmp(all->cmd->arg[0], "exit"))
	//     cmd_exit(arg);
}