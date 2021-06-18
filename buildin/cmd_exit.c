#include "../minishell.h"

int		exit_error(t_all *all, char *cmd, char *arg, int k)
{
	printf("%s\n", all->cmd[k].arg[0]);
	write(1, "minishell: ", PROMPT);
	printf("%s: %s: %s\n", cmd, arg, "numeric argument required");
	all->status = "255";
	exit (0);
	// return (0);
}

void	print_exit(t_all *all, int k)
{
	printf("%s\n", all->cmd[k].arg[0]);
	// exit (0);
}

int	isdigit_line(char *str)
{
	int		c;

	c = 0;
	while (str[c])
    {
        if (ft_isdigit(str[c]))
		    c++;
        else
            return (0);   
    }
	return (1);
}

void	cmd_exit(t_all *all, char **arg, int k)
{
	char	*status;
	int		stts;

	if (all->cmd[k].arg[1])
	{
		if (isdigit_line(all->cmd[k].arg[1]))
		{
			if (!all->cmd[k].arg[2])
			{
				print_exit(all, k);
				stts = ft_atoi(all->cmd[k].arg[1]);
				stts %= 255;
				printf("stts - atoi = %d\n", stts);
				status = ft_itoa(stts);
				printf("status - itoa = %s\n", all->status);
				// status = " ";
				exit (0);
			}
			else
			{
                printf("%s\n", all->cmd[k].arg[0]);
				write(1, "minishell: ", PROMPT);
				printf("%s: %s \n", all->cmd[k].arg[0], "too many arguments");
				status = "1";
			}
		}
		else
		{
			exit_error(all, all->cmd[k].arg[0], all->cmd[k].arg[1], k);
			// all->status = "255";
			// exit (0);
		}
	}
	else
	{
		print_exit(all, k);
		all->status = "0";
		exit (0);
	}
}