#include "../minishell.h"

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
	int		i;
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
	// int		stat;

	i = 0;
	pid = fork();
	signal(SIGINT, int_sign);
	signal(SIGQUIT, quit_sign);
	signal(EOF, kill_sig);
	if (!pid)
	{
		while (all->path_arr[i])
		{
			if (ft_strncmp(name, "./", 2) == 0 || ft_strrncmp(name, "/minishell", 10) == 0)
			{
				path = add_path(all, all->tline.env_arr);
				cmd = ft_strjoin(path, name);
				exec = execve(name, arg, all->tline.env_arr);
				if (!errno)
				{
					status = 1;
					exit (status);
				}
			}
			else
			{
				if (!cmp_path(all, all->path_arr[i], name))
					cmd = ft_strjoin(all->path_arr[i], name);
				else if (all->path_arr[0])
					cmd = ft_strjoin(all->path_arr[i], all->tline.new_name);
				exec = execve(cmd, arg, all->tline.env_arr);
				if (!errno)
				{
					status = 1;
					exit (status);
				}
			}
			if (exec == -1)
				i++;
			if (all->path_arr[i] == NULL && exec == -1)
			{
				if (ft_strncmp(name, "/", 1))
					printf("minishell: %s: command not found\n", arg[0]);
				else if (!ft_strncmp(name, "/", 1))
					printf("minishell: %s: %s\n", arg[0], strerror(2));			
			}
		}
	}
	else if (pid < 0)
		printf("%s\n", strerror(errno));
	else
		waitpid(pid, &status, 0);
	WIFEXITED(status);
	WEXITSTATUS(status);
	return (status);
}

void    buildin_func(t_all *all, char **arg, char **envp)
{
	int i;

	i = all->cmd_i;
	all->cmd_i++;
	if (!ft_strcmp(all->cmd[i].arg[0], "cd"))
		cmd_cd(all, all->tline.env_arr, i);
	else if (!ft_strcmp(all->cmd[i].arg[0], "echo"))
		cmd_echo(all, arg, i);
	else if (!ft_strcmp(all->cmd[i].arg[0], "pwd"))
		cmd_pwd(all, envp);
	else if (!ft_strcmp(all->cmd[i].arg[0], "export"))
		cmd_export(all, i);
	else if (!ft_strcmp(all->cmd[i].arg[0], "unset"))
	    cmd_unset(all, i);
	else if (!ft_strcmp(all->cmd[i].arg[0], "env"))
		cmd_env(all, i);
	else if (!ft_strcmp(all->cmd[i].arg[0], "exit"))
	    cmd_exit(all, arg, i);
	else
		status = execute(all, all->cmd[i].arg[0], all->cmd[i].arg, envp) / 256;
}