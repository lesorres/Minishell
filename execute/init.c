#include "../minishell.h"

void	split_path_line(t_all *all, int i)
{
	char	*tmp;
	char	*tmp_2;
	int		line_len;

	line_len = ft_strlen(all->tline.env_arr[i]);
	tmp = ft_substr(all->tline.env_arr[i], 5, (line_len - 5));
	tmp_2 = ft_strtrim(tmp, "\'\"");
	free(tmp);
	all->path_arr = ft_split(tmp_2, ':');
	if (all->path_arr[0] == NULL)
		check_if_path_arr_exists(all);
	else
	{
		i = 0;
		while (all->path_arr[i])
		{
			line_len = ft_strlen(all->path_arr[i]) + 2;
			all->path_arr[i] = ft_realloc(all->path_arr[i], line_len);
			all->path_arr[i][line_len - 2] = '/';
			i++;
		}
	}
	free(tmp_2);
}

void	split_path(t_all *all)
{
	int		i;

	i = 0;
	while (all->tline.env_arr[i])
	{
		if (ft_strncmp(all->tline.env_arr[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (all->tline.env_arr[i] == NULL)
		all->path_arr = NULL;
	else
		split_path_line(all, i);
}

void	line_init(t_all *all, struct termios *term)
{
	set_terminal(term);
	all->line = ft_calloc(1024, sizeof(char));
	all->tline.print_line = malloc(1024);
	all->tline.print_line[0] = '\0';
	all->tline.cursor = PROMPT;
	all->tline.symb_num = PROMPT;
	all->tline.curr_line = all->tline.line_num;
	write(1, "#minishell> ", PROMPT);
	ft_putstr_fd(save_cursor, 1);
	all->trm.str[0] = 0;
	all->count = 0;
}

void	free_cmd_lines(t_all *all)
{
	int	i;

	i = 0;
	if (all->cmd)
	{
		while (!all->cmd[i].null && all->cmd[i].arg)
		{
			__free_arr(all->cmd[i].arg);
			i++;
		}
		free (all->cmd);
		all->cmd = NULL;
	}
	free(all->line);
	free(all->tline.print_line);
	all->tline.line_num++;
}

void	__free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
