#include "minishell.h"

void cmd_echo(t_cmd *cmd, char **argv)
{
    int     i;
    int     j;
    
    i = 1;
    while (argv[i])
    {
        j = 0;
        while (argv[i][j])
        {
            write(1, argv[i][j++], 1);
            if (strcmp(argv[1], "-n"))
                i = 2;    
            else
                write(1, "\n", 1);
            i++;
        }
    }
}

void cmd_cd(t_cmd *cmd, char **argv, char **envp)
{
    int     dir;

    if (argv[1])
    {
        dir = chdir(argv[1]);
        printf("%s", dir);
    }
    else if (!argv[1])
        chdir("/");
}

void    cmd_pwd(t_cmd *cmd, char **arg, char **envp)
{
    char *path;
    char *tmp;

    path = malloc(sizeof(char) * PATH_LEN);
    if (!path)
        return (NULL);
    getcwd(tmp, PATH_LEN);
    if (ft_strlen(tmp) > PATH_LEN)
        path = ft_realloc(tmp, PATH_LEN * 2);
    ft_strcpy(path, tmp);
    printf("%s/n", path);
    free (tmp);
    free (path);
}

void    cmd_env(char **envp)
{
    int     i;

    i = 0;
    while (envp[i])
    {
        printf("%s\n", envp[i]);
        i++;
    }
    return (1);
}

void    buildin_func(t_cmd *cmd, char **arg, char **envp)
{
    if (strcmp(arg[0], "cd "))
        cmd_cd(cmd, arg, envp);
    else if (strcmp(arg[0], "echo "))
        cmd_echo(cmd, arg);
    else if (strcmp(arg[0], "pwd"))
        cmd_pwd(cmd, arg, envp);
    else if (strcmp(arg[0], "export"))
        cmd_export(cmd, arg, envp);
    else if (strcmp(arg[0], "unset "))
        cmd_unset(cmd, arg, envp);
    else if (strcmp(arg[0], "env"))
        cmd_env(envp);
    else if (strcmp(arg[0], "exit"))
        cmd_exit(arg);
}