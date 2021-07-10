#include "../minishell.h"

void	up_arrow(t_all *all)
{
	int		hist_fd;
	char	*tmp;

	ft_putstr_fd(restore_cursor, 1);
	ft_putstr_fd(tgetstr("ce", 0), 1);
	hist_fd = open(all->file_name, O_RDONLY);
	tmp = all->line;
	if (all->tline.curr_line > 0)
	{
		all->tline.curr_line--;
		all->line = get_hist_line(all->tline.curr_line, hist_fd);
		free (tmp);
		all->tline.cursor = ft_strlen(all->line) + PROMPT;
		all->tline.symb_num = ft_strlen(all->line) + PROMPT;
		all->count = ft_strlen(all->line);
		write(1, all->line, ft_strlen(all->line));
	}
	close(hist_fd);
}

void	down_arrow_2(t_all *all)
{
	write(1, all->tline.print_line, ft_strlen(all->tline.print_line));
	free(all->line);
	all->line = ft_calloc(1024, sizeof(char));
	all->line = ft_strcpy(all->line, all->tline.print_line);
	all->count = ft_strlen(all->line);
}

void	down_arrow(t_all *all)
{
	int		hist_fd;
	char	*tmp;

	ft_putstr_fd(restore_cursor, 1);
	ft_putstr_fd(tgetstr("ce", 0), 1);
	hist_fd = open(all->file_name, O_RDONLY);
	tmp = all->line;
	if (all->tline.curr_line < all->tline.line_num && all->line[0] != '\n')
	{
		all->tline.curr_line++;
		all->line = get_hist_line(all->tline.curr_line, hist_fd);
		free (tmp);
		all->tline.cursor = ft_strlen(all->line) + PROMPT;
		all->tline.symb_num = ft_strlen(all->line) + PROMPT;
		all->count = ft_strlen(all->line);
		write(1, all->line, ft_strlen(all->line));
	}
	else if (all->tline.curr_line == all->tline.line_num)
		down_arrow_2(all);
	close(hist_fd);
}

void	left_arrow(t_all *all)
{
	if (all->tline.cursor > PROMPT)
	{
		all->tline.cursor--;
		ft_putstr_fd(tgetstr("le", 0), 1);
	}
}

void	right_arrow(t_all *all)
{
	if (all->tline.symb_num > all->tline.cursor)
	{
		all->tline.cursor++;
		ft_putstr_fd(tgetstr("nd", 0), 1);
	}
}
