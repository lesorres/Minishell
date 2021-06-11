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
	int		i;;

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

int	execute(t_all *all, char *name, char **arg, char **envp)
{
	char	*cmd;
	pid_t	pid;
	int		i;

	i = 0;
	pid = fork();
	if (!pid)
	{
		while (all->path_arr[i])
		{
			all->path_arr[i] = ft_strjoin(all->path_arr[i], "/");
			cmd = ft_strjoin(all->path_arr[i], name);
			if (execve(cmd, arg, envp) == -1)
				i++;
			// else
			// {
			// 	exit (0);
			// 	break ;
			// }
				// printf("child pid - %i\n", pid);
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

	// i = 0;
	i = all->cmd_n - 2;
			// printf("%s\n", all->cmd[i].name);
	// while (!all->cmd[i].null && all->cmd[i].arg)
	// {
		// printf("arg[0] = %s\n", arg[0]);
		// printf("arg[1] = %s\n", arg[1]);
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
		// i++;
		//void	split_path(t_all *all);
	// }
}