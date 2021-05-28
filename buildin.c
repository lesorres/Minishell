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
        char    *tmp_path;
        // tmp_user = malloc(PATH_LEN);
        tmp_path = getenv("HOME");
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

void    sort_env(t_all *all)
{
    int     i;
    int     j;
    char    *tmp_line;

    i = 0;
    while (i++ < all->tline.env_line_num)
    {
        j = 0;
        while (j < all->tline.env_line_num - 1)
        {
            if (ft_strcmp(all->tline.env_arr[i], all->tline.env_arr[i + 1] > 0))
            {
                tmp_line = malloc(sizeof(ft_strlen(all->tline.env_arr[i])));
                tmp_line = all->tline.env_arr[i + 1];
                all->tline.env_arr[i + 1] = all->tline.env_arr[i];
                all->tline.env_arr[i] = tmp_line;
                free(tmp_line);
            }
            j++;
        }
    }
}

void    add_new_env_param(t_all *all)
{
    
}

void    cmd_env(t_all *all, char **envp)
{
    int     i;

    i = 0;
    while (all->tline.env_arr[i])
        printf("%s\n", all->tline.env_arr[i++]);
}

void    cmd_export(t_all *all, char **argv)
{
    if (!all->cmd[0].arg[1])
        sort_env(all);
    else
        add_new_env_param(all);
}

void    get_envp(t_all *all, char **envp)
{
    int     line;
    
    all->tline.env_line_num = 0;
    line = 0;
    while (envp[all->tline.env_line_num])
        all->tline.env_line_num++;
    all->tline.env_arr = (char **)malloc(sizeof(char *) * (all->tline.env_line_num));
    while (all->tline.env_line_num)
    {
        all->tline.env_arr[line] = ft_strdup(envp[line]);
        line++;
        all->tline.env_line_num--;
    }
    // int i = 0;
    // while (all->tline.env_arr[i])
    //     printf("%s\n", all->tline.env_arr[i++]);
}

void    buildin_func(t_all *all, char **arg, char **envp)
{
    get_envp(all, envp);
    if (!strcmp(all->cmd[0].arg[0], "cd"))
        cmd_cd(all, arg, envp);
    else if (!strcmp(all->cmd[0].arg[0], "echo"))
        cmd_echo(all, arg);
    if (!strcmp(all->cmd[0].arg[0], "pwd"))
        cmd_pwd(all, arg, envp);
    else if (!strcmp(all->cmd->arg[0], "export"))
        cmd_export(all, arg);
    // else if (strcmp(all->cmd->arg[0], "unset "))
    //     cmd_unset(all, arg, envp);
    else if (!strcmp(all->cmd[0].arg[0], "env"))
        cmd_env(all, envp);
    // else if (strcmp(all->cmd->arg[0], "exit"))
    //     cmd_exit(arg);
}