#include "../minishell.h"

void	status_exit(void)
{
	status = 1;
	exit (status);
}

void	cmd_errors(t_all *all, char *name, char **arg)
{
	if (ft_strncmp(name, "/", 1) && ft_strncmp(name, "./", 2))
	{
		print_err2(arg[0], "command not found");
		all->status = 127;
		exit(all->status);
	}
	else if (!ft_strncmp(name, "/", 1) && name[1] == '\0')
	{
		print_err2(arg[0], strerror(21));
		status = 126;
		exit(status);
	}
	else if (!ft_strncmp(name, "/", 1) || !ft_strncmp(name, "./", 2))
	{
		print_err2(arg[0], strerror(2));
		status = 1;
		exit(status);
	}
}

int	cmp_cmd_path(t_all *all, char *line, char **arg, char *name)
{
	char	*cmd;
	int		exec;
	char	*path;

	if (ft_strncmp(name, "./", 2) == 0
		|| ft_strrncmp(name, "/minishell", 10) == 0)
	{
		exec = execve(name, arg, all->tline.env_arr);
		if (!errno)
			status_exit();
	}
	else
	{
		if (!cmp_path(all, line, name))
			cmd = ft_strjoin(line, name);
		else if (all->path_arr[0])
			cmd = ft_strjoin(line, all->tline.new_name);
		exec = execve(cmd, arg, all->tline.env_arr);
		if (!errno)
			status_exit();
	}
	return (exec);
}

void	child_process_cycle(t_all *all, char *name, char **arg)
{
	int		i;
	int		exec;

	i = 0;
	while (all->path_arr)
	{
		exec = cmp_cmd_path(all, all->path_arr[i], arg, name);
		if (exec == -1)
			i++;
		if (all->path_arr[i] == NULL && exec == -1)
			cmd_errors(all, name, arg);
	}
}

int	execute(t_all *all, char *name, char **arg, char **envp)
{
	pid_t	pid;

	pid = fork();
	signal(SIGINT, int_sign);
	signal(SIGQUIT, quit_sign);
	if (!pid)
	{
		if (all->path_arr == NULL)
		{
			print_err2(arg[0], strerror(2));
			status = 127;
		}
		child_process_cycle(all, name, arg);
	}
	else if (pid < 0)
		printf("%s\n", strerror(errno));
	else
		waitpid(pid, &status, 0);
	WIFEXITED(status);
	WEXITSTATUS(status);
	return (status);
}
