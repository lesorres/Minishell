#include "../minishell.h"

int		exit_error(t_all *all, char *cmd, char *arg, int k)
{
	printf("%s\n", all->cmd[k].arg[0]);
	write(1, "minishell: ", PROMPT);
	printf("%s: %s: %s\n", cmd, arg, "numeric argument required");
	return (0);
}

void	print_exit(t_all *all, int k)
{
	printf("%s\n", all->cmd[k].arg[0]);
	exit (0);
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
	if (all->cmd[k].arg[1])
	{
		if (isdigit_line(all->cmd[k].arg[1]))
		{
			if (!all->cmd[k].arg[1])
				print_exit(all, k);
			else
			{
                printf("%s\n", all->cmd[k].arg[0]);
				write(1, "minishell: ", PROMPT);
				printf("%s: %s \n", all->cmd[k].arg[0], "too many arguments");
			}
		}
		else
		{
			exit_error(all, all->cmd[k].arg[0], all->cmd[k].arg[1], k);
			exit (0);
		}
	}
	else
		print_exit(all, k);
}