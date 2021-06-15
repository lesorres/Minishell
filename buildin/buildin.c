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
	char	*tmp;
	char	*new_name;

	i = 0;
	j = int_strrchr(name, 47);
	// printf("this string - %s, this j = %d\n", name, j);
	len = ft_strlen(name);
	// printf("len = %d\n", len);
	tmp = ft_substr(name, 0, len - j);
	// printf("tmp = %s\n", tmp);
	// while (arr[i])
	// {
		int	cmp = ft_strncmp(str, tmp, ft_strlen(tmp));
		// printf("arr[%i] = %s, cmp = %d\n", i, str, cmp);
		if (!cmp)
		{
			all->tline.new_name = malloc(sizeof(len - j));
			all->tline.new_name = ft_substr(name, (j + 1), len - j);
			printf("new name - %s\n", all->tline.new_name);
			return(1);
		}
		// i++;
	// }
	return (0);
}

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
		// printf("[%i] - %s\n", i, all->path_arr[i]);
		i++;
	}
		i = 0;
		while (all->path_arr[i])
		{
		// printf("name - %s\n", name);
			if (ft_strrncmp(name, "/minishell", 10) != 0)
			{
				
				// printf("ft_strrncmp(%s, %s) = %d\n", name, "/minishell", ft_strrncmp(name, "/minishell", 10));
				if (!cmp_path(all, all->path_arr[i], name))
				{
					cmd = ft_strjoin(all->path_arr[i], name);
					printf("cmd ------------- %s\n", cmd);
				}
				else
					cmd = ft_strjoin(all->path_arr[i], all->tline.new_name);
				exec = execve(cmd, arg, all->tline.env_arr);
			}
			else if (ft_strrncmp(name, "/minishell", 10) == 0)
				exec = execve(name, arg, all->tline.env_arr);
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
	{
		execute(all, all->cmd[i].arg[0], all->cmd[i].arg, envp);
		// printf("execute arg[0] = %s\n", all->cmd[i].arg[0]);
	}
}