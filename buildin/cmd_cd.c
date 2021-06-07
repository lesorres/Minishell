#include "../minishell.h"

int	error_handler(char *arg1, char *arg2, char *err)
{
	write(1, "minishell: ", PROMPT);
	printf("%s: %s: %s\n", arg1, arg2, err);
	return(1);
}


	// j = ft_strchr_int(line, '=');
	// cmp = ft_strlen(line) - 1;
	// if (j == 0)
	// 	j = ft_strlen(line);
	// return (j);
	// j = find_equal_sign(all, line);
	// tmp = ft_substr(line, 0, j);

void	srch_str_in_arr(t_all *all, )
{
	int		i;

	i = 0;
	while ()	
}

int cmd_cd(t_all *all, char **envp, int k)
{
	char    *path;
	char    *tmp_path;
	int		error_num;

	path = malloc(PATH_LEN + 1);
	all->builds.oldpwd = getcwd(path, PATH_LEN);
	if (all->cmd[k].arg[0] && ft_strcmp(all->cmd[k].arg[0], "."))
	{
		if (chdir(all->cmd[k].arg[0]) == -1)
			error_handler(all->cmd[k].name, all->cmd[k].arg[0], strerror(errno));
	}
	else if (!all->cmd[k].arg[0] || !ft_strcmp(all->cmd[k].arg[0], "."))
	{
		tmp_path = getenv("HOME");
		chdir(tmp_path);
	}                                        // обработать добавление OLDPWD в массив env и export
	printf("path --- %s\n", tmp_path);
	add_new_env_param(all, all->builds.oldpwd);
	free(path);
	return (0);
}