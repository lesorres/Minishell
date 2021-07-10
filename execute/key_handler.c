#include "../minishell.h"

void	backspace_arrow(t_all *all)
{
	if (all->tline.cursor > PROMPT)
	{
		all->tline.cursor--;
		all->tline.symb_num--;
		all->tline.print_line[all->count--] = '\0';
		ft_putstr_fd(cursor_left, 1);
		ft_putstr_fd(tgetstr("dc", 0), 1);
	}
	if (all->tline.cursor == PROMPT)
	{
		all->line[0] = '\0';
		all->tline.print_line[0] = '\0';
	}
}

void	exit_key(int fd)
{
	write (1, "exit\n", 5);
	close (fd);
	exit (0);
}

void	ctrl_c(t_all *all)
{
	write(1, "\n#minishell> ", PROMPT + 1);
	ft_putstr_fd(save_cursor, 1);
	all = (void *)all;
}

void	write_line(t_all *all)
{
	all->tline.cursor += write(1, all->trm.str, all->trm.l);
	all->tline.print_line[all->count] = all->trm.str[0];
	all->tline.print_line[all->count + 1] = 0;
	all->line[all->count] = all->trm.str[0];
	all->line[all->count + 1] = 0;
	all->count++;
}

void	check_if_path_arr_exists(t_all *all)
{
	free_path_arr(all);
	all->path_arr = NULL;
}
