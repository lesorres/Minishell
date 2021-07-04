#include "minishell.h"

void	int_sign(int sign)
{
	status = 130;
	if (sign == SIGINT)
	{
		write(1, "\n", 1);
		signal(SIGINT, int_sign);
	}
}

void	quit_sign(int sign)
{
	status = 131;
	if (sign == SIGQUIT)
		write(1, "\n", 1);
}
