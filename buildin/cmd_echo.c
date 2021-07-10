#include "../minishell.h"

void	cmd_echo(t_all *all, int k)
{
	int	i;

	i = 1;
	if (all->cmd[k].arg[i] == NULL && all->cmd[k].echo_n != 1)
	{
		write(1, "\n", 1);
		return ;
	}
	else
	{
		while (!all->cmd[k].null && all->cmd[k].arg[i])
		{
			write(1, all->cmd[k].arg[i], ft_strlen(all->cmd[k].arg[i]));
			if (!(all->cmd[k].arg[i + 1] == 0))
				write(1, " ", 1);
			i++;
		}
	}
	if (all->cmd[k].echo_n != 1)
		write(1, "\n", 1);
	g_status = 0;
}
