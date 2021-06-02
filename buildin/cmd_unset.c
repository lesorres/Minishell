#include "../minishell.h"

void    del_env_line(t_all *all, char *line)
{
    char    **new_arr;
    int     i;


}

int    cmd_unset(t_all *all, int k)
{
    int i;

    i = 0;
    if (!all->cmd[k].arg[0])
        return (0);
    else
    {
        while (all->cmd[k].arg[i])
        {
            del_env_line(all, all->cmd[k].arg[i]);
            i++;
        }
    }
    return(1);
}