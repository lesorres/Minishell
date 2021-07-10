#include "../minishell.h"

int	hist_line_num(int fd)
{
	char	c;
	int		i;

	i = 0;
	while (read(fd, &c, 1) > 0)
	{
		if (c == '\n')
			i++;
	}
	return (i);
}

char	*get_hist_line(int num, int fd)
{
	char	c;
	int		i;
	char	*str;

	i = 0;
	while (i < num)
	{
		read(fd, &c, 1);
		if (c == '\n')
			i++;
	}
	str = malloc(1024);
	i = 0;
	while (read(fd, &c, 1) > 0 && c != '\n')
		str[i++] = c;
	str[i] = '\0';
	return (str);
}

void	set_terminal(struct termios *term)
{
	term->c_lflag &= ~(ECHO);
	term->c_lflag &= ~(ICANON);
	term->c_lflag &= ~(ISIG);
	tcsetattr(0, TCSANOW, term);
}

void	res_terminal(struct termios *term)
{
	term->c_lflag |= ECHO | ICANON | ISIG;
	tcsetattr(0, TCSANOW, term);
}
