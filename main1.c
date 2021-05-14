#include "minishell.h"

void	scroll_history(char *str)
{
	int	l;
	

	// str = read_line(0);
	// l = ft_strlen(str);
	l = read(1, str, 100);
	if (!strcmp(str, UP)) // || !strcmp(str, OPT_UP) || !strcmp(str, SHF_UP) || !strcmp(str, CTRL_UP))
	{
		ft_putstr_fd(restore_cursor, 1);
		ft_putstr_fd(tigetstr("ed"), 1);
		write(1, "prev", 4);
	}
	else if (!strcmp(str, DWN)) //|| !strcmp(str, OPT_DWN) || !strcmp(str, SHF_DWN) || !strcmp(str, CTRL_DWN))
	{
		ft_putstr_fd(restore_cursor, 1);
		ft_putstr_fd(tigetstr("ed"), 1);
		write(1, "next", 4);
	}
	else if (!strcmp(str, key_backspace) || !strcmp(str, "\177"))
	{
		ft_putstr_fd(cursor_left, 1);
		ft_putstr_fd(tgetstr("dc", 0), 1);
	}
	else
		write(1, str, l);
}

int main(int argc, char const **argv)
{
	int     fd = 0;
	// char    *str;
	char	str[2000];
	int     l;
	struct  termios term;
	char    *term_name = "xterm-256color";

	tcgetattr(0, &term);
	// term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);
	tgetent(0, term_name);

	while (strcmp(str, "\4"))
	{
		ft_putstr_fd(save_cursor, 1);
		// do 
		// {
		// 	l = read(0, str, 100);
		// 	if (!strcmp(str, "\e[A") || !strcmp(str, OPT_UP) || !strcmp(str, SHF_UP) || !strcmp(str, CTRL_UP))
		// 	{
		// 		ft_putstr_fd(restore_cursor, 1);
		// 		ft_putstr_fd(tigetstr("ed"), 1);
		// 		write(1, "prev", 4);
		// 	}
		// 	else if (!strcmp(str, DWN) || !strcmp(str, OPT_DWN) || !strcmp(str, SHF_DWN) || !strcmp(str, CTRL_DWN))
		// 	{
		// 		ft_putstr_fd(restore_cursor, 1);
		// 		ft_putstr_fd(tigetstr("ed"), 1);
		// 		write(1, "next", 4);
		// 	}
		// 	else if (!strcmp(str, key_backspace) || !strcmp(str, "\177"))
		// 	{
		// 		ft_putstr_fd(cursor_left, 1);
		// 		ft_putstr_fd(tgetstr("dc", 0), 1);
		// 	}
		// 	else
		// 		write(1, str, l);
		// } while (strcmp(str, "\n") || strcmp(str, "\4"));
		scroll_history(str);
		while (strcmp(str, "\n") || strcmp(str, "\4"))
			scroll_history(str);
	}
	write(1, "\n", 1);
	return (0);
}