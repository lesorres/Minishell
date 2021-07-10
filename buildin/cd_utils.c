#include "../minishell.h"

int	error_handler(char *arg1, char *arg2, char *err)
{
	write(2, "minishell: ", PROMPT);
	write(2, arg1, ft_strlen(arg1));
	write(2, ": ", 2);
	write(2, arg2, ft_strlen(arg2));
	write(2, ": ", 2);
	write(2, err, ft_strlen(err));
	write(2, "\n", 1);
	return (1);
}

void	add_oldpwd(t_all *all, char *path)
{
	int		i;

	i = 0;
	while (all->tline.env_arr[i])
	{
		if (ft_strncmp(all->tline.env_arr[i], "OLDPWD=", 7) == 0)
		{
			all->trm.oldpwd = ft_strjoin("OLDPWD=", path);
			all->tline.env_arr[i] = ft_realloc(all->tline.env_arr[i],
					ft_strlen(all->trm.oldpwd) + 1);
			ft_strcpy(all->tline.env_arr[i], all->trm.oldpwd);
			free(all->trm.oldpwd);
			break ;
		}
		i++;
	}
	if (all->tline.env_arr[i] == NULL && all->trm.oldpwd == NULL)
	{
		all->trm.oldpwd = ft_strjoin("OLDPWD=", path);
		add_new_env_param(all, all->trm.oldpwd);
		free(all->trm.oldpwd);
	}
}

char	*add_path(t_all *all)
{
	char	*path;

	path = NULL;
	path = getcwd(path, PATH_LEN);
	return (path);
	all = (void *)all;
}
