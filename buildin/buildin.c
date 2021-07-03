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

void	print_err2(t_all *all, char *cmd, char *err_name)
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, err_name, ft_strlen(err_name));
	write(2, "\n", 1);
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
	// signal(EOF, kill_sig);
	if (!pid)
	{
		if (all->path_arr == NULL)
		{
			print_err2(all, arg[0], strerror(2));
			status = 127;
		} 
		while (all->path_arr)       // all->path_arr[i]
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
				if (ft_strncmp(name, "/", 1) && ft_strncmp(name, "./", 2))
				{
					print_err2(all, arg[0], "command not found");
					all->status = 127;
					// write(2, "minishell: ", 11);
					// write(2, arg[0], ft_strlen(arg[0]));
					// write(2, ": command not found\n", 20);
					exit(status);
				}
				else if (!ft_strncmp(name, "/", 1) && name[1] == '\0')
				{
					print_err2(all, arg[0], strerror(21));
					status = 126;
					exit(status);
				}
				else if (!ft_strncmp(name, "/", 1) || !ft_strncmp(name, "./", 2))
				{
					print_err2(all, arg[0], strerror(2));
					status = 1;
					// printf("minishell: %s: %s\n", arg[0], strerror(2));
					exit(status);
				}
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
	int dp1;
	int dp2;

	i = all->cmd_i;
	all->cmd_i++;
	// write (all->out, "cmd num in buildin = ", 21);
	// char *bla = ft_itoa(i);
	// write (all->out, bla, 1);
	// write (all->out, "\n\n", 2);
	// write (all->out, "o_rdir before if = ", 19);
	// char *bla1 = ft_itoa(all->cmd[i].o_rdir);
	// write (all->out, bla1, 1);
	// write (all->out, "\n\n", 2);
	// printf ("o_rdir before if= %i\n", all->cmd[i].o_rdir);
	if (all->cmd[i].i_rdir == -1 || all->cmd[i].o_rdir == -1)
        return;
	if (all->cmd[i].i_rdir != 0)
	{
		dp1 = dup2(all->cmd[i].i_rdir, 0);
		close(all->cmd[i].i_rdir);
	}
	if (all->cmd[i].o_rdir != 1)
	{
		// printf ("o_rdir in buildin = %i\n", all->cmd[i].o_rdir);
		dp2 = dup2(all->cmd[i].o_rdir, 1);
		close(all->cmd[i].o_rdir);
	}
	// printf("i_rdir buildin = %i\n", dp1);
	// printf("o_rdir buildin = %i\n", dp2);
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
	{
		status = execute(all, all->cmd[i].arg[0], all->cmd[i].arg, envp);
		if (status > 256)
			status /= 256;
		if (all->status != 0)
		{
			status = all->status;
			all->status = 0;
		}
	}
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
	// 	close(all->cmd[i].o_rdir);
}