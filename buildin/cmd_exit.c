#include "../minishell.h"

int	exit_error(t_all *all, char *cmd, char *arg, int k)
{
	printf("%s\n", all->cmd[k].arg[0]);
	write(1, "minishell: ", PROMPT);
	printf("%s: %s: %s\n", cmd, arg, "numeric argument required");
	g_status = 255;
	all->status = 255;
	exit (255);
}

void	print_exit(char *cmd)
{
	int		stts;

	stts = ft_atoi(cmd);
	if (stts > 256)
		stts %= 256;
	else if (stts < 0)
	{
		stts %= 256;
		stts = 256 + stts;
	}
	g_status = stts;
	printf("%s\n", cmd);
	exit (g_status);
}

int	isdigit_line(char *str)
{
	int		c;

	c = 0;
	while (str[c])
	{
		if (str[0] == '-' || ft_isdigit(str[c]))
			c++;
		else
			return (1);
	}
	return (0);
}

void	cmd_exit(t_all *all, int k)
{
	if (all->cmd[k].arg[1])
	{
		if (!isdigit_line(all->cmd[k].arg[1]))
		{
			if (!all->cmd[k].arg[2])
				print_exit(all->cmd[k].arg[0]);
			else
			{
				printf("%s\n", all->cmd[k].arg[0]);
				write(1, "minishell: ", PROMPT);
				printf("%s: %s \n", all->cmd[k].arg[0], "too many arguments");
				g_status = 1;
			}
		}
		else
			exit_error(all, all->cmd[k].arg[0], all->cmd[k].arg[1], k);
	}
	else
	{
		printf("%s\n", all->cmd[k].arg[0]);
		g_status = 0;
		exit (0);
	}
}
