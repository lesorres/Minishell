#include "../minishell.h"

void cmd_echo(t_all *all, char **argv, int k)
{
	int     i;
	
	i = 0;
	while (!all->cmd[k].null && all->cmd[k].arg[i])          // аргументы echo в парсере должны обрабатываться как один
	{
		if (!ft_strcmp(all->cmd[k].arg[0], "-n"))
			i = 1;    
		write(1, all->cmd[k].arg[i], ft_strlen(all->cmd[k].arg[i]));
		if (ft_strcmp(all->cmd[k].arg[0], "-n"))
			write(1, "\n", 1);
		i++;
	}
}