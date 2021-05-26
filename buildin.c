#include "minishell.h"

void cmd_echo(t_all *all, char **argv)
{
    int     i;
    int     j;
    
    i = 1;
    while (all->cmd[0].arg[i])
    {
        // j = 0;
        // while (argv[i][j])
        {
            write(1, all->cmd[0].arg[i], ft_strlen(all->cmd[0].arg[i]));
            if (strcmp(all->cmd[0].arg[i], "-n"))
                i = 2;    
            else
                write(1, "\n", 1);
            i++;
        }
    }
}

void cmd_cd(t_all *all, char **argv, char **envp)
{
    int     dir;

    if (all->cmd[0].arg[1])
    {
        dir = chdir(all->cmd[0].arg[1]);
        // printf("%s", dir);
    }
    else if (!all->cmd[0].arg[1])
    {
        char    *tmp_user;
        // tmp_user = malloc(PATH_LEN);
        tmp_user = getenv("USER");
        char    *tmp_path = ft_strjoin("/Users/", tmp_user);
        chdir(tmp_path);
    }
}

int		ft_putstr(char *str)
{
	int	i;
	int	ret;

	i = -1;
	ret = 0;
	while (str[++i])
		ret += write(1, &str[i], 1);
	return (ret);
}

void    cmd_pwd(t_all *all, char **arg, char **envp)
{
    char    *path;
    char    *tmp;

    path = malloc(PATH_LEN + 1);
    tmp = getcwd(path, PATH_LEN);
    write(1, tmp, ft_strlen(tmp));
    write(1, "\n", 1);
    free(path);
    (void)arg;
}

void    cmd_env(char **envp)
{
    int     i;

    i = 0;
    while (envp[i])
    {
        printf("%d - %s\n", i, envp[i]);
        i++;
    }
}

// void    buildin_func(t_all *all, char **arg, char **envp)
// {
//     if (strcmp(arg[0], "cd "))
//         cmd_cd(all, arg, envp);
//     else if (strcmp(arg[0], "echo "))
//         cmd_echo(all, arg);
//     else if (strcmp(arg[0], "pwd"))
//         cmd_pwd(all, arg, envp);
//     else if (strcmp(arg[0], "export"))
//         cmd_export(all, arg, envp);
//     else if (strcmp(arg[0], "unset "))
//         cmd_unset(all, arg, envp);
//     else if (strcmp(arg[0], "env"))
//         cmd_env(envp);
//     else if (strcmp(arg[0], "exit"))
//         cmd_exit(arg);
// }

void    buildin_func(t_all *all, char **arg, char **envp)
{
    if (!strcmp(all->cmd[0].arg[0], "cd"))
        cmd_cd(all, arg, envp);
    else if (!strcmp(all->cmd[0].arg[0], "echo"))
        cmd_echo(all, arg);
    // printf("%s\n", all->cmd->arg[0]);
    // write(1, all->cmd[0].arg[0], ft_strlen(arg[0]));
    if (!strcmp(all->cmd[0].arg[0], "pwd"))
        cmd_pwd(all, arg, envp);
    // else if (strcmp(all->cmd->arg[0], "export"))
    //     cmd_export(all, arg, envp);
    // else if (strcmp(all->cmd->arg[0], "unset "))
    //     cmd_unset(all, arg, envp);
    else if (!strcmp(all->cmd[0].arg[0], "env"))
        cmd_env(envp);
    // else if (strcmp(all->cmd->arg[0], "exit"))
    //     cmd_exit(arg);
}