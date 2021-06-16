#include "../minishell.h"

int	error_handler(char *arg1, char *arg2, char *err)
{
	write(1, "minishell: ", PROMPT);
	printf("%s: %s: %s\n", arg1, arg2, err);
	return(1);
}

void	srch_str_in_arr(t_all *all, char *tmp)
{
	int		i;
	char	*pwd;

	i = 0;
	pwd = ft_strjoin("PWD=", tmp);
	while (all->tline.env_arr[i])
	{
		if (ft_strncmp(all->tline.env_arr[i], "PWD=", 4))
			i++;
		else 
			break ;
	}
	if (all->tline.env_arr[i] == NULL)
		add_new_line_to_arr(&all->tline.env_arr, pwd);
	else
	{
		all->tline.env_arr[i] = ft_realloc(all->tline.env_arr[i], ft_strlen(pwd));
		ft_strcpy(all->tline.env_arr[i], pwd);
	}
}

// void	srch_str_in_arr(t_all *all, char *tmp)
// {
// 	int		i;
// 	char	*pwd;
// 	char	*tmp_pwd;

// 	i = 0;
// 	pwd = ft_strjoin("PWD=", tmp);
// 	printf("srch_str_in_arr: pwd = %s\n", pwd);
// 	while (ft_strncmp(all->tline.env_arr[i], "PWD=", 4))
// 		i++;
// 	if (all->tline.env_arr[i] == NULL)
// 		add_new_line_to_arr(&all->tline.env_arr, pwd);
// 	else
// 	{
// 		all->tline.env_arr[i] = ft_realloc(all->tline.env_arr[i], ft_strlen(pwd));
// 		ft_strcpy(all->tline.env_arr[i], pwd);
// 	}
// 	tmp_pwd = ft_substr(pwd, 4, (ft_strlen(pwd)) - 4);
// 	free(pwd);
// 	pwd = ft_strjoin(tmp_pwd, "/");
// 	all->tline.pwd = malloc(sizeof(ft_strlen(pwd)));
// 	ft_strcpy(all->tline.pwd, pwd);
// 	free(pwd);
// 	free(tmp_pwd);
// }

void	add_oldpwd(t_all *all, char *path)
{
	int		i;

	i = 0;
	while (all->tline.env_arr[i])
	{
		if (ft_strncmp(all->tline.env_arr[i], "OLDPWD=", 7) == 0)
			{
				all->builds.oldpwd = ft_strjoin("OLDPWD=", path);
				all->tline.env_arr[i] = ft_realloc(all->tline.env_arr[i], ft_strlen(all->builds.oldpwd));
				ft_strcpy(all->tline.env_arr[i], all->builds.oldpwd);
				break ;
			}
		i++;
	}
	if (all->tline.env_arr[i] == NULL && all->builds.oldpwd == NULL)
	{
		all->builds.oldpwd = ft_strjoin("OLDPWD=", path);
		add_new_env_param(all, all->builds.oldpwd);
	}
}

char	*add_path(t_all *all, char **envp)
{
	char    *path;

	path = malloc(PATH_LEN + 1);
	path = getcwd(path, PATH_LEN);
	return (path);
}

void	cmd_cd(t_all *all, char **envp, int k)
{
	char    *path;
	char    *tmp_path;
	char	*tmp;
	int		i;

	path = add_path(all, envp);
	all->builds.oldpwd = NULL;
	if (all->cmd[k].arg[1] && ft_strcmp(all->cmd[k].arg[1], "."))
	{
		if (chdir(all->cmd[k].arg[1]) == -1)
			error_handler(all->cmd[k].arg[0], all->cmd[k].arg[1], strerror(errno));
		else
		{
			i = 0;
			tmp = getcwd(tmp, PATH_LEN);
			srch_str_in_arr(all, tmp);
		}
	}
	else if (!all->cmd[k].arg[1])
	{
		tmp_path = getenv("HOME");
		chdir(tmp_path);
	}
	add_oldpwd(all, path);
	free(path);
	// free(tmp);
}