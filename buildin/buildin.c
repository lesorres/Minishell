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

void    buildin_func(t_all *all, char **arg, char **envp)
{
	all->builds.export_new_arg = 0;
	if (!strcmp(all->cmd[0].arg[0], "cd"))
		cmd_cd(all, envp);
	else if (!strcmp(all->cmd[0].arg[0], "echo"))
		cmd_echo(all, arg);
	if (!strcmp(all->cmd[0].arg[0], "pwd"))
		cmd_pwd(all, envp);
	else if (!strcmp(all->cmd[0].arg[0], "export"))
		cmd_export(all, envp);
	// else if (strcmp(all->cmd->arg[0], "unset "))
	//     cmd_unset(all, arg, envp);
	else if (!strcmp(all->cmd[0].arg[0], "env"))
		cmd_env(all);
	else if (!strcmp(all->cmd->arg[0], "exit"))
	    cmd_exit(all, arg);
}