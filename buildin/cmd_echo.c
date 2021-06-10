#include "../minishell.h"

void cmd_echo(t_all *all, char **argv, int k)
{
	int     i;
	int		f;
	
	f = 0;
	i = 1;
	if (all->cmd[k].arg[i] == NULL)
	{
		write(1, "\n", 1);
		return ;
	}
	if (!ft_strcmp(all->cmd[k].arg[1], "-n"))
	{
		i++;
		f = 1;
	}
	while (!all->cmd[k].null && all->cmd[k].arg[i])          // аргументы echo в парсере должны обрабатываться как один
	{
		write(1, all->cmd[k].arg[i], ft_strlen(all->cmd[k].arg[i]));
		// if (!ft_strcmp(all->cmd[k].arg[1], "-n"))
		// // else
		// 	write(1, "\n", 1);
		// else
		if (!(all->cmd[k].arg[i + 1] == 0))
			write(1, " ", 1);
		i++;
	}
	if (f != 1)
		write(1, "\n", 1);
}