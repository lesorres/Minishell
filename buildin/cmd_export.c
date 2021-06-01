#include "../minishell.h"

void	copy_env(t_all *all)
{
	int     i;
	int		j;
	
	j = 0;
	i = 0;
	while (all->tline.env_arr[j])
		j++;
	all->tline.export_arr = (char **)malloc(sizeof(char *) * (j + 1)); //возможна утечка
	all->tline.export_arr[j] = NULL;
	while (all->tline.env_arr[i])
	{
		all->tline.export_arr[i] = ft_strdup(all->tline.env_arr[i]);
		i++;
	}
	// all->tline.export_arr[i] = NULL;
}

void    sort_env(t_all *all)
{
	int     j;
	int 	sort;
	char 	*tmp;

	sort = 0;
	while (!sort)
	{
		sort = 1;
		j = 0;
		while (all->tline.export_arr[j + 1] != NULL)
		{
			if (ft_strncmp(all->tline.export_arr[j], all->tline.export_arr[j + 1]) > 0)
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

void    cmd_export(t_all *all, char **envp)
{
	int i;
    int arr_len;
	
	i = 0;
	arr_len = len(all->tline.export_arr);
	if (all->cmd[0].arg[1])
	{
        // проверять есть ли такая переменная окружения в массиве, если да - заменять значение
		add_new_env_param(all, all->cmd[0].arg[1]);
		all->builds.export_new_arg = 1;
	}
	arr_len = len(all->tline.export_arr);
	copy_env(all);
	sort_env(all);
	i = 0;
	while (all->tline.export_arr[i])
	{
	    printf("declare -x %s\n", all->tline.export_arr[i]);
		i++;
	}
}