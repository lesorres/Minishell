#include "../minishell.h"

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
		add_new_env_param(all, pwd);
	else
	{
		all->tline.env_arr[i] = ft_realloc(all->tline.env_arr[i],
				ft_strlen(pwd) + 1);
		ft_strcpy(all->tline.env_arr[i], pwd);
	}
	free(pwd);
}

int	find_var_in_arr(char **arr, char *str)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		if (ft_strncmp(arr[i], str, ft_strlen(str)) == 0)
			break ;
		i++;
	}
	if (arr[i] == NULL)
		i = -1;
	return (i);
}

void	check_home(t_all *all, int k, char	*tmp)
{
	char	*tmp_path;

	tmp_path = getenv("HOME");
	chdir(tmp_path);
	if (find_var_in_arr(all->tline.env_arr, "HOME=") == -1)
	{
		print_err2(all->cmd[k].arg[0], "HOME not set");
		g_status = 1;
	}
	getcwd(tmp, PATH_LEN);
	srch_str_in_arr(all, tmp);
}

void	check_cd_args(t_all *all, int k, char *tmp)
{
	int		dir;

	dir = chdir(all->cmd[k].arg[1]);
	if (dir == -1)
	{
		error_handler(all->cmd[k].arg[0], all->cmd[k].arg[1], strerror(errno));
		g_status = 1;
	}
	else
	{
		getcwd(tmp, PATH_LEN);
		srch_str_in_arr(all, tmp);
		g_status = 0;
	}
}

void	cmd_cd(t_all *all, int k)
{
	char	*path;
	char	*tmp;

	path = add_path(all);
	all->trm.oldpwd = NULL;
	tmp = malloc(sizeof(char) * PATH_LEN);
	if (all->cmd[k].arg[1] && ft_strcmp(all->cmd[k].arg[1], "."))
		check_cd_args(all, k, tmp);
	else if (!all->cmd[k].arg[1])
		check_home(all, k, tmp);
	else if (!ft_strcmp(all->cmd[k].arg[1], "."))
	{
		getcwd(tmp, PATH_LEN);
		srch_str_in_arr(all, tmp);
		g_status = 0;
	}
	add_oldpwd(all, path);
	free(path);
	free(tmp);
}
