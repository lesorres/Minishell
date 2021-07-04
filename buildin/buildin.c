#include "../minishell.h"

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

void	

int	execute(t_all *all, char *name, char **arg, char **envp)
{
	char	*cmd;
	pid_t	pid;
	int		i;
	int		exec;
	char	*path;

	i = 0;
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
		while (all->path_arr)
		{
			if (ft_strncmp(name, "./", 2) == 0
				|| ft_strrncmp(name, "/minishell", 10) == 0)
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
				cmd_errors(all, name, arg);
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

void	replace_fd(t_all *all, int i)
{
	int	dp1;
	int	dp2;

	if (all->cmd[i].i_rdir == -1 || all->cmd[i].o_rdir == -1)
		return ;
	if (all->cmd[i].i_rdir != 0)
	{
		dp1 = dup2(all->cmd[i].i_rdir, 0);
		close(all->cmd[i].i_rdir);
	}
	if (all->cmd[i].o_rdir != 1)
	{
		dp2 = dup2(all->cmd[i].o_rdir, 1);
		close(all->cmd[i].o_rdir);
	}
}

void	close_fds(t_all *all, int i)
{
	if (all->cmd[i].i_rdir != 0)
	{
		close(all->cmd[i].i_rdir);
		dup2(all->in, 0);
	}
	if (all->cmd[i].o_rdir != 1)
	{
		close(all->cmd[i].o_rdir);
		dup2(all->out, 1);
	}
}

void	executer(t_all *all, char **arg, char **envp, int i)
{
	status = execute(all, all->cmd[i].arg[0], all->cmd[i].arg, envp);
	if (status >= 256)
		status /= 256;
	if (all->status != 0)
	{
		status = all->status;
		all->status = 0;
	}
}

void	buildin_func(t_all *all, char **arg, char **envp)
{
	int	i;

	i = all->cmd_i;
	all->cmd_i++;
	replace_fd(all, i);
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
		executer(all, all->cmd[i].arg, envp, i);
	close_fds(all, i);
}
