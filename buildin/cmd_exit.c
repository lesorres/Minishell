#include "../minishell.h"

int		exit_error(t_all *all, char *cmd, char *arg, int k)
{
	printf("%s\n", all->cmd[k].arg[0]);
	write(1, "minishell: ", PROMPT);
	printf("%s: %s: %s\n", cmd, arg, "numeric argument required");
	status = 255;
	exit (1);
	// return (0);
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
	status = stts;
	printf("%s\n", cmd);
	exit (status);
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

void	cmd_exit(t_all *all, char **arg, int k)
{

	if (all->cmd[k].arg[1])                            // exit ...
	{
		if (!isdigit_line(all->cmd[k].arg[1]))
		{
			if (!all->cmd[k].arg[2])                   //exit 123
				print_exit(all->cmd[k].arg[1]);
			else                                       //exit 123 hgrfe
			{
                printf("%s\n", all->cmd[k].arg[0]);
				write(1, "minishell: ", PROMPT);
				printf("%s: %s \n", all->cmd[k].arg[0], "too many arguments");
				status = 1;
			}
		}
		else                                           //exit qwr 123
			exit_error(all, all->cmd[k].arg[0], all->cmd[k].arg[1], k);
	}
	else                                               // exit\n
	{
		printf("%s\n", all->cmd[k].arg[0]);
		status = 0;
		exit (0);
	}
}