#include "minishell.h"

// void	scroll_history(char *str, int fd, t_termline *tline)
// {
// }

// void	execute(t_cmd *cmd)
// {
// 	// if (cmd->echo != -1)
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

int	count_hist_lines(t_all *all)
{
	int		i;

	i = 0;
	while (all->hist_arr[i])
		i++;
	return (i);
}

static int len(char **str)
{
    int	i;

	i = 0;
	while (str && str[i])
		i++;
    i += 1;
	return (i);
}

int add_last_line(char ***input, char *line)
{
    char    **out;
    int     i;
    
    i = len(*input);
    if(!(out = (char**)malloc(sizeof(char*) * (i + 1))))
        return(0);
    out[i] = NULL;
    out[--i] = line;
    while (i--)
        out[i] = (*input)[i];
    free(*input);
    *input = out;
    return(1);
}

char **create_arr(int i)
{
    char **out;

    if (i < 1)
        i = 1;
    out = (char**)malloc(sizeof(char*) * i);
    while (i--)
        out[i] = NULL;
    return (out); 
}

void	init_all(t_all *all)
{
	all->hist_arr = create_arr(0);
}

void	rewrite_hist(t_all *all, char *line)
{
	int	fd;

	fd = open(".HISTORY", O_RDWR | O_CREAT | O_APPEND, 0777);
	ft_putstr_fd(line, fd);
	close(fd);
	add_last_line(&all->hist_arr, line);
}

void	init_hist(t_all *all)
{
	int	fd;
	char	*line;

	fd = open(".HISTORY", O_RDWR | O_CREAT | O_APPEND, 0777);
	line = NULL;
	get_next_line(fd, &line);
	while (*line)
	{
		add_last_line(&all->hist_arr, line);
		get_next_line(fd, &line);
	}
	close(fd);
}

int main(int argc, char **argv, char **envp)
{
	t_cmd cmd;
	t_all	all;
	t_termline tline;
	char	*str;
	int     l;
	int		i;
	struct  termios term;
	int	count;
	int		k;

	// i = 
	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);
	tgetent(0, TERM_NAME);
	str = (char *)malloc(sizeof(char) * 100);
	// tline.line_num = count_hist_lines(fd);
	while (strcmp(str, "\4"))
	{	
		tline.cursor = PROMPT;
		tline.symb_num = PROMPT;
		write(1, "#minishell> ", PROMPT);
		ft_putstr_fd(save_cursor, 1);
		str[0] = 0;
		count = 0;
		while (strcmp(str, "\n") && strcmp(str, "\4"))
		{
			if (tline.symb_num < tline.cursor)
				tline.symb_num = tline.cursor;
			l = read(1, str, 100);
			str[l] = 0;
			if (!strcmp(str, UP) || !strcmp(str, OPT_UP) || !strcmp(str, SHF_UP) || !strcmp(str, CTRL_UP))
			{
				ft_putstr_fd(restore_cursor, 1);
				ft_putstr_fd(tgetstr("ce", 0), 1);
				// write(1, "prev", 4);
				// ft_strcpy(tline.hist_line, all.hist_arr[i]);
				// printf();
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
					tline.symb_num--;
					ft_putstr_fd(cursor_left, 1);
					ft_putstr_fd(tgetstr("dc", 0), 1);
				}
			}
			else if (!strcmp(str, LEFT))
			{
				if (tline.cursor > PROMPT)
				{
					tline.cursor--;
					ft_putstr_fd(tgetstr("le", 0), 1);
				}
			}
			else if (!strcmp(str, RiGHT))
			{
				if (tline.symb_num > tline.cursor)
				{
					tline.cursor++;
					ft_putstr_fd(tgetstr("nd", 0), 1);
				}
			}
			else
			{
				tline.cursor += write(1, str, l);
				count++;
			}
			// fd += write(fd, str, l);
		}
		// printf("str - %s\n", &str[2]);
		// printf("str - %p\n", &str);
		// printf("str - %c\n", str[2]);
		// str[count] = '\0';
		// printf("%i\n", count);
		// parser(&str[1], &all);
		// printf("pars - %s\n", all.cmd[0].arg[0]);
		// printf("hist line - %s\n", all.hist_arr[k++]);
		// scroll_history(str, fd);
			// scroll_history(str, fd, &tline);
	}
	// execute(&com);
	// buildin_func(&all, argv, envp);
	free (str);
	write(1, "\n", 1);
	// close (fd);
	return (0);
}