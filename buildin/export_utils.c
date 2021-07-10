#include "../minishell.h"

void	sort_env(t_all *all)
{
	int		j;
	int		sort;
	char	*tmp;

	sort = 0;
	while (!sort)
	{
		sort = 1;
		j = 0;
		while (all->tline.export_arr[j + 1] != NULL)
		{
			if (ft_strcmp(all->tline.export_arr[j],
					all->tline.export_arr[j + 1]) > 0)
			{
				tmp = all->tline.export_arr[j];
				all->tline.export_arr[j] = all->tline.export_arr[j + 1];
				all->tline.export_arr[j + 1] = tmp;
				sort = 0;
				break ;
			}
			j++;
		}
	}
}

void	copy_env(t_all *all)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (all->tline.env_arr[j])
		j++;
	if (all->tline.export_arr != NULL)
	{
		while (all->tline.export_arr[i])
			free (all->tline.export_arr[i++]);
		free (all->tline.export_arr);
	}
	i = 0;
	all->tline.export_arr = (char **)malloc(sizeof(char *) * (j + 1));
	all->tline.export_arr[j] = NULL;
	while (all->tline.env_arr[i])
	{
		all->tline.export_arr[i] = ft_strdup(all->tline.env_arr[i]);
		i++;
	}
	sort_env(all);
}

int	find_equal_sign(t_all *all, char *line)
{
	int		j;
	int		cmp;

	j = ft_strchr_int(line, '=');
	cmp = ft_strlen(line) - 1;
	if (j == -1)
	{
		all->tline.equal_sign = 0;
		j = ft_strlen(line);
	}
	else if (j == cmp)
		all->tline.equal_sign = 1;
	return (j);
}

int	find_env_equal(char *line)
{
	int		j;
	int		cmp;

	j = ft_strchr_int(line, '=');
	cmp = ft_strlen(line) - 1;
	if (j == -1)
		j = ft_strlen(line);
	return (j);
}

char	*add_quotes(t_all *all, char *line)
{
	char	*tmp;
	int		len;

	len = 0;
	tmp = NULL;
	if (all->tline.equal_sign == 0)
		len = ft_strlen(line) + 3;
	if (all->tline.equal_sign == 0)
		tmp = ft_strjoin(line, "=");
	if (tmp)
		tmp[len] = '\0';
	return (tmp);
}
