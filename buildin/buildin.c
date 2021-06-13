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

// void    add_new_line_to_arr(char **arr, char *line)
// {
// 	char	**new_arr;
// 	int		i;;

// 	i = len(arr);
// 	if(!(new_arr = calloc((i + 1), sizeof(char *))))
// 		printf("error");
// 	new_arr[i] = NULL;
// 	new_arr[--i] = line;
// 	while (i--)
// 		new_arr[i] = arr[i];
// 	free(arr);
// 	arr = new_arr;
// }

int	execute(t_all *all, char *name, char **arg, char **envp)
{
	char	*cmd;
	pid_t	pid;
	int		i;
	int		exec;
	char	*tmp;

	i = 0;
	pid = fork();
	if (!pid)
	{
		while (all->path_arr[i])
		{
			// tmp = ft_strjoin(all->path_arr[i], "/");

			// all->path_arr[i] = ft_strjoin(all->path_arr[i], "/");  //leak
			printf("path_arr %s\n", all->path_arr[i]);
			cmd = ft_strjoin(all->path_arr[i], name);
			printf("cmd before  %s\n", cmd);
			exec = execve(cmd, arg, all->tline.env_arr);
			// printf("cmd %s\n", cmd);
			if (exec == -1)
				i++;
			if (all->path_arr[i] == NULL && exec == -1)
				printf("%s: %s: %s\n", "minishell", arg[0], "command not found");
			// 	all->tline.first_shlvl = 2;
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

	i = all->cmd_n - 2;
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