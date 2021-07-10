#include "../minishell.h"

int	len(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	i += 1;
	return (i);
}

void	add_new_env_param(t_all *all, char *line)
{
	char	**new_arr;
	int		i;

	i = len(all->tline.env_arr);
	new_arr = ft_calloc((i + 1), sizeof(char *));
	if (!new_arr)
		write(2, strerror(errno), ft_strlen(strerror(errno)));
	new_arr[i] = NULL;
	free(new_arr[i - 1]);
	new_arr[--i] = ft_strdup(line);
	while (i--)
		new_arr[i] = all->tline.env_arr[i];
	free(all->tline.env_arr);
	all->tline.env_arr = new_arr;
}

int	int_strrchr(char *s, int c)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == c)
			return (i);
		i--;
	}
	return (0);
}

int	cmp_path(t_all *all, char *str, char *name)
{
	int		j;
	int		len;
	int		cmp;
	char	*tmp;

	j = int_strrchr(name, 47);
	len = ft_strlen(name);
	tmp = ft_substr(name, 0, len - j);
	cmp = ft_strncmp(str, tmp, ft_strlen(tmp));
	free(tmp);
	if (!cmp)
	{
		all->tline.new_name = ft_substr(name, (j + 1), len - j);
		return (1);
	}
	return (0);
}

void	print_err2(char *cmd, char *err_name)
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, err_name, ft_strlen(err_name));
	write(2, "\n", 1);
}
