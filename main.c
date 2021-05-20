#include "minishell.h"

void	scroll_history(char *str, int fd, t_termline *tline)
{
}

// void	execute(t_command *com)
// {
// 	// if (com->echo != -1)
// 	// 	cmd_echo()
// 	int		stdin;
// 	int		stdout;
// 	pid_t	pid;

// 	pid = fork();
// 	if (!pid)
// 		execve();
// 	else if (pid < 0)
// 		printf("%s\n", "Error!");
// 	else
// 		wait(&pid);
// 	return (1);
// }

int main(int argc, char **argv, char **env)
{
	t_command com;
	t_termline tline;
	int		fd;
	char	str[2000];
	int     l;
	struct  termios term;

	fd = open(".HISTORY", O_RDWR | O_CREAT, 0777);
	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);
	tgetent(0, TERM_NAME);
	while (strcmp(str, "\4"))
	{	
		tline.cursor = PROMPT;
		tline.num_symb = PROMPT;
		write(1, "#minishell> ", PROMPT);
		ft_putstr_fd(save_cursor, 1);
		while (!strcmp(str, "\n") || strcmp(str, "\4"))
		{
			if (tline.num_symb < tline.cursor)
				tline.num_symb = tline.cursor;
			l = read(1, str, 100);
			str[l] = 0;
			if (!strcmp(str, UP) || !strcmp(str, OPT_UP) || !strcmp(str, SHF_UP) || !strcmp(str, CTRL_UP))
			{
				ft_putstr_fd(restore_cursor, 1);
				ft_putstr_fd(tgetstr("ce", 0), 1);
				write(1, "prev", 4);
			}
			else if (!strcmp(str, DWN) || !strcmp(str, OPT_DWN) || !strcmp(str, SHF_DWN) || !strcmp(str, CTRL_DWN))
			{
				ft_putstr_fd(restore_cursor, 1);
				ft_putstr_fd(tgetstr("ce", 0), 1);
				write(1, "next", 4);
			}
			else if (!strcmp(str, key_backspace) || !strcmp(str, "\177"))
			{	
				if (tline.cursor > PROMPT)
				{
					tline.cursor--;
					tline.num_symb--;
					ft_putstr_fd(cursor_left, 1);
					ft_putstr_fd(tgetstr("dc", 0), 1);
				}
			}
			else if (!strcmp(str, LEFT))
			{
				if (tline.cursor > PROMPT)
				{
					tline.cursor--;
					ft_putstr_fd(cursor_left, 1);
					ft_putstr_fd(tgetstr("le", 0), 1);
				}
			}
			else if (!strcmp(str, RiGHT))
			{
				if (tline.num_symb > tline.cursor)
				{
					tline.cursor++;
					ft_putstr_fd(cursor_right, 1);
					ft_putstr_fd(tgetstr("ri", 0), 1);
				}
			}
			else
				tline.cursor += write(1, str, l);
			fd += write(fd, str, l);
		}
		// scroll_history(str, fd);
			// scroll_history(str, fd, &tline);
	}
	// execute(&com);
	write(1, "\n", 1);
	close (fd);
	return (0);
}