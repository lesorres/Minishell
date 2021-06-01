#include "../minishell.h"

void cmd_echo(t_all *all, char **argv)
{
	int     i;
	int     j;
	
	i = 1;
	j = 0;
	while (!all->cmd[0].null && all->cmd[0].arg[i])          // аргументы echo в парсере должны обрабатываться как один
	{
		if (!ft_strncmp(all->cmd[0].arg[1], "-n"))
			i = 2;    
		write(1, all->cmd[0].arg[i], ft_strlen(all->cmd[j].arg[i]));
		if (ft_strncmp(all->cmd[0].arg[1], "-n"))
			write(1, "\n", 1);
		i++;
	}
}