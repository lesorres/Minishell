#include "minishell.h"

void    int_sign(int sign)
{
    if (sign == SIGINT)
    {
        write(1, "\n", 1);
        // write(1, "#minishell> ", PROMPT);
        signal(SIGINT, int_sign);
    }
}

void    quit_sign(int sign)
{
    if (sign == SIGQUIT)
        write(1, "Quit: 3\n", 9);
}

void    kill_sig(int sign)
{
    if (sign == SIGKILL)
    {
        write(1, "exit\n", 5);
        exit (1);
    }
}