#include "../minishell.h"

void	cmp_char(t_all *all)
{
	if (all->tline.symb_num < all->tline.cursor)
		all->tline.symb_num = all->tline.cursor;
	all->trm.l = read(1, all->trm.str, 10);
	all->trm.str[all->trm.l] = 0;
	if (!ft_strcmp(all->trm.str, UP))
		up_arrow(all);
	else if (!ft_strcmp(all->trm.str, DWN))
		down_arrow(all);
	else if (!ft_strcmp(all->trm.str, key_backspace)
		|| !ft_strcmp(all->trm.str, "\177"))
		backspace_arrow(all);
	else if (!ft_strcmp(all->trm.str, K_LEFT))
		left_arrow(all);
	else if (!ft_strcmp(all->trm.str, K_RIGHT))
		right_arrow(all);
	else if (!ft_strcmp(all->trm.str, "\003"))
		ctrl_c(all);
	else if (ft_isprint(all->trm.str[0]) || all->trm.str[0] == '\n')
		write_line(all);
	if (!all->tline.print_line[0] && !all->line[0]
		&& !ft_strcmp(all->trm.str, "\4"))
		exit_key(all->trm.fd);
}

void	write_ch(t_all *all, struct termios *term, char **arg, char **envp)
{
	line_init(all, term);
	while (ft_strcmp(all->trm.str, "\n"))
		cmp_char(all);
	if (!all->tline.print_line[0] && !all->line[0]
		&& !ft_strcmp(all->trm.str, "\4"))
		exit_key(all->trm.fd);
	if (all->line[0] != '\n')
		write(all->trm.fd, all->line, ft_strlen(all->line));
	all->line[all->count - 1] = 0;
	all->tline.print_line[all->count - 1] = 0;
	res_terminal(term);
	parser(all, arg, envp);
	free_cmd_lines(all);
}

void	init_all_var(t_all *all, struct termios *term, char **arg, char **envp)
{
	all->in = dup(STDIN_FILENO);
	all->out = dup(STDOUT_FILENO);
	all->tline.path = NULL;
	all->tline.path = getcwd(all->tline.path, PATH_LEN);
	all->file_name = ft_strjoin(all->tline.path, "/.HISTORY");
	g_status = 0;
	all->status = 0;
	get_envp(all, envp);
	all->trm.str = ft_calloc(10, sizeof(char));
	all->trm.fd = open(all->file_name, O_RDWR | O_CREAT, 0777);
	all->tline.line_num = hist_line_num(all->trm.fd);
	while (all->trm.str)
		write_ch(all, term, arg, envp);
	close(all->trm.fd);
	write(1, "\n", 1);
	free (all->trm.str);
}

void	find_line_in_arr(char **arr, char *line)
{
	int		i;
	int		j;
	int		num;
	char	*tmp;

	i = 0;
	while (ft_strnstr(arr[i], line, ft_strlen(line)))
		i++;
	if (ft_strncmp(arr[i], line, ft_strlen(line)))
		add_new_line_to_arr(&arr, line);
	else
	{
		j = find_env_equal(arr[i]) + 1;
		num = ft_strlen(arr[i]) - j;
		tmp = ft_substr(arr[i], j, num);
	}
}

int	main(int argc, char **arg, char **envp)
{
	struct termios	term;
	t_all			all;

	tcgetattr(0, &term);
	tgetent(0, TERM_NAME);
	init_all_var(&all, &term, arg, envp);
	return (0);
	argc = 0;
}
