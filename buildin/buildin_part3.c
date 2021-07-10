#include "../minishell.h"

void	cmd_errors(t_all *all, char *name, char **arg)
{
	if (ft_strncmp(name, "/", 1) && ft_strncmp(name, "./", 2))
	{
		print_err2(arg[0], "command not found");
		all->status = 127;
		exit(all->status);
	}
	else if ((!ft_strncmp(name, "/", 1) && name[1] != '\0')
		|| (!ft_strncmp(name, "./", 2) && name[2] != '\0'))
	{
		print_err2(arg[0], strerror(2));
		g_status = 127;
	}
	else if ((!ft_strncmp(name, "/", 1) && name[1] == '\0')
		|| (!ft_strncmp(name, "./", 2) && name[2] == '\0'))
	{
		print_err2(arg[0], strerror(21));
		g_status = 126;
	}
	exit(g_status);
}

void	error_handler2(char *cmd, t_all *all, char *name, char **arg)
{
	free (cmd);
	cmd_errors(all, name, arg);
}

int	cmp_cmd_path(t_all *all, char *line, char **arg, char *name)
{
	char	*cmd;
	int		exec;

	cmd = NULL;
	if (ft_strncmp(name, "./", 2) == 0
		|| ft_strrncmp(name, "/minishell", 10) == 0)
	{
		exec = execve(name, arg, all->tline.env_arr);
		if (!errno)
			cmd_errors(all, name, arg);
	}
	else
	{
		if (!cmp_path(all, line, name))
			cmd = ft_strjoin(line, name);
		else if (all->path_arr[0])
			cmd = ft_strjoin(line, all->tline.new_name);
		exec = execve(cmd, arg, all->tline.env_arr);
		if (!errno)
			error_handler2(cmd, all, name, arg);
		if (cmd)
			free (cmd);
	}
	return (exec);
}

void	child_process_cycle(t_all *all, char *name, char **arg)
{
	int		i;
	int		exec;

	i = 0;
	if (!check_path_exist(all))
	{
		while (all->path_arr)
		{
			exec = cmp_cmd_path(all, all->path_arr[i], arg, name);
			if (exec == -1)
				i++;
			if (all->path_arr[i] == NULL && exec == -1)
				cmd_errors(all, name, arg);
		}
		if (all->path_arr == NULL)
			cmd_errors(all, name, arg);
	}
	else
	{
		exec = execve(name, arg, all->tline.env_arr);
		if (exec == -1)
			cmd_errors(all, name, arg);
		g_status = 127;
		exit (g_status);
	}
}

int	execute(t_all *all, char *name, char **arg)
{
	pid_t	pid;

	pid = fork();
	signal(SIGINT, int_sign);
	signal(SIGQUIT, quit_sign);
	if (!pid)
		child_process_cycle(all, name, arg);
	else if (pid < 0)
		printf("%s\n", strerror(errno));
	else
		waitpid(pid, &g_status, 0);
	WIFEXITED(g_status);
	WEXITSTATUS(g_status);
	WIFSIGNALED(g_status);
	return (g_status);
}
