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

void    buildin_func(t_all *all, char **arg, char **envp)   //как-то нужно проверять команды, которые не cmd[0] !?!?!?!?!?!
{
	int i;

	i = 0;
			// printf("%s\n", all->cmd[i].name);
	while (!all->cmd[i].null && all->cmd[i].arg)
	{
		if (!strcmp(all->cmd[i].name, "cd"))
			cmd_cd(all, envp, i);
		else if (!strcmp(all->cmd[i].name, "echo"))
			cmd_echo(all, arg, i);
		else if (!strcmp(all->cmd[i].name, "pwd"))
			cmd_pwd(all, envp);
		else if (!strcmp(all->cmd[i].name, "export"))
			cmd_export(all, i);
		else if (!strcmp(all->cmd[i].name, "unset"))
		    cmd_unset(all, i);
		else if (!strcmp(all->cmd[i].name, "env"))
			cmd_env(all, i);
		else if (!strcmp(all->cmd[i].name, "exit"))
		    cmd_exit(all, arg, i);
		i++;
	}
}