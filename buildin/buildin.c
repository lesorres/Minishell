#include "../minishell.h"

void		print_arr(char **args)
{
	int i;

	i = 0;
	while (args[i])
	{
		printf("%s\n", args[i]);
		i++;
	}
	if (args[i] == NULL)
		printf("<null>\n");
}

int len(char **str)
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
	int		i;

	i = len(all->tline.env_arr);
	if(!(new_arr = calloc((i + 1), sizeof(char *))))
		printf("error");
	new_arr[i] = NULL;
	new_arr[--i] = line;
	while (i--)
		new_arr[i] = all->tline.env_arr[i];
	free(all->tline.env_arr);
	all->tline.env_arr = new_arr;
}

int	int_strrchr(char *s, int c)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == c)
			return (i);
		i--;
	}
	return (0);
}

int		cmp_path(t_all *all, char *str, char *name)   
{
	int		i;  // arr - all->path_arr; name - arg[0];
	int		j;
	int		len;
	int		cmp;
	char	*tmp;
	char	*new_name;

	i = 0;
	j = int_strrchr(name, 47);
	len = ft_strlen(name);
	tmp = ft_substr(name, 0, len - j);
	cmp = ft_strncmp(str, tmp, ft_strlen(tmp));
	if (!cmp)
	{
		all->tline.new_name = malloc(sizeof(len - j));
		all->tline.new_name = ft_substr(name, (j + 1), len - j);
		return(1);
	}
	return (0);
}

int	execute(t_all *all, char *name, char **arg, char **envp)
{
	char	*cmd;
	pid_t	pid;
	int		i;
	int		exec;
	char	*tmp;
	char	*path;

	i = 0;
	pid = fork();
	signal(SIGINT, int_sign);
	signal(SIGQUIT, quit_sign);
	if (!pid)
	{
		while (all->path_arr[i])
		{
			if (ft_strncmp(name, "./", 2) == 0 || ft_strrncmp(name, "/minishell", 10) == 0)
			{
				path = add_path(all, all->tline.env_arr);
				cmd = ft_strjoin(path, name);
				exec = execve(name, arg, all->tline.env_arr);
			}
			else
			{
				if (!cmp_path(all, all->path_arr[i], name))
					cmd = ft_strjoin(all->path_arr[i], name);
				else
					cmd = ft_strjoin(all->path_arr[i], all->tline.new_name);
				exec = execve(cmd, arg, all->tline.env_arr);
			}
			// else if (ft_strrncmp(name, "/minishell", 10) == 0)
			// 	exec = execve(name, arg, all->tline.env_arr);
			if (exec == -1)
				i++;
			if (all->path_arr[i] == NULL && exec == -1)
			{
				printf("%s: %s: %s\n", "minishell", arg[0], strerror(errno));

			}
		}
	}
	else if (pid < 0)
	{
		printf("%s\n", "Error!");
		exit (1);
	}
	else
		wait(&pid);
	return (1);
}

void    buildin_func(t_all *all, char **arg, char **envp)
{
	int i;

	i = all->cmd_n - 2;
	printf("arg[0] = %s\n", all->cmd[i].arg[0]);
	// while (!all->cmd[i].null && all->cmd[i].arg)
	if (!strcmp(all->cmd[i].arg[0], "cd"))
		cmd_cd(all, envp, i);
	else if (!strcmp(all->cmd[i].arg[0], "echo"))
		cmd_echo(all, arg, i);
	else if (!strcmp(all->cmd[i].arg[0], "pwd"))
		cmd_pwd(all, envp);
	else if (!strcmp(all->cmd[i].arg[0], "export"))
		cmd_export(all, i);
	else if (!strcmp(all->cmd[i].arg[0], "unset"))
	    cmd_unset(all, i);
	else if (!strcmp(all->cmd[i].arg[0], "env"))
		cmd_env(all, i);
	else if (!strcmp(all->cmd[i].arg[0], "exit"))
	    cmd_exit(all, arg, i);
	else
		execute(all, all->cmd[i].arg[0], all->cmd[i].arg, envp);
}