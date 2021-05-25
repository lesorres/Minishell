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
    if(!(out = (char**)calloc((i + 1), sizeof(char*))))  //malloc
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
    out = (char**)calloc(i, sizeof(char*));
    while (i--)
        out[i] = NULL;
    return (out); 
}

void	init_all(t_all *all)
{
	all->hist_arr = create_arr(0);
	all->tline.str = NULL;
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
		free(line);
	}
	close(fd);
}

static int line_len(char *str)
{
    int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int add_l_char(char **line, char ch) //нужно переписать
{
    int i;
    char *out;
    char *tmp;

    tmp = *line;
    i = ft_strlen(tmp);
    if(!(out = malloc(sizeof(char) * (i + 2))))
        return (0);
	ft_strcpy(out, tmp);
	out[i++] = ch;
    out[i] = '\0';
    free(*line);
    *line = out;
    return (1);
}

void	free_hisr_arr(t_all *all)
{
	int	i;
	
	i = 0;
	while (all->hist_arr[i])
	{
		free(all->hist_arr[i]);
		i++;
	}
	free (all->hist_arr);
}

int		hist_line_num(int fd)
{
	char	c;
	int		i;

	i = 0;
	while(read(fd, &c, 1) > 0)
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
	while(i < num)
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

int main(int argc, char **argv, char **envp)
{
	t_cmd 	cmd;
	t_all	all;
	t_termline tline;
	char	*str;
	int     l;
	int		i;
	struct  termios term;
	int		count;
	int		k;
	int		fd;

	fd = open(".HISTORY", O_RDWR | O_CREAT, 0777);
	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);
	tgetent(0, TERM_NAME);
	str = (char *)malloc(sizeof(char) * 100);
	tline.line_num = hist_line_num(fd);
	// init_all(&all);
	// init_hist(&all);
	// rewrite_hist(&all, str);
	while (strcmp(str, "\4"))
	{	
		all.tline.str = malloc(1024);
		all.tline.cursor = PROMPT;
		all.tline.symb_num = PROMPT;
		write(1, "#minishell> ", PROMPT);
		ft_putstr_fd(save_cursor, 1);
		str[0] = 0;
		count = 0;
		tline.curr_line = tline.line_num;
		while (strcmp(str, "\n") && strcmp(str, "\4"))
		{
			if (all.tline.symb_num < all.tline.cursor)
				all.tline.symb_num = all.tline.cursor;
			l = read(1, str, 20);
			str[l] = 0;
			if (!strcmp(str, UP) || !strcmp(str, OPT_UP) || !strcmp(str, SHF_UP) || !strcmp(str, CTRL_UP))
			{
				int		hist_fd;
				char	*tmp;

				ft_putstr_fd(restore_cursor, 1);
				ft_putstr_fd(tgetstr("ce", 0), 1);
				hist_fd = open(".HISTORY", O_RDONLY);
				tmp = all.tline.str;
				all.tline.str = get_hist_line(tline.curr_line, hist_fd);
				free (tmp);
				all.tline.cursor = ft_strlen(all.tline.str) + PROMPT;
				all.tline.symb_num = ft_strlen(all.tline.str) + PROMPT;
				count = ft_strlen(all.tline.str);
				if (tline.curr_line-- > 0)
					write(1, all.tline.str, ft_strlen(all.tline.str));
				else
					write(1, all.tline.str, ft_strlen(all.tline.str));
				close(hist_fd);
			}
			else if (!strcmp(str, DWN) || !strcmp(str, OPT_DWN) || !strcmp(str, SHF_DWN) || !strcmp(str, CTRL_DWN))
			{
				int		hist_fd;
				char	*tmp;

				ft_putstr_fd(restore_cursor, 1);
				ft_putstr_fd(tgetstr("ce", 0), 1);
				hist_fd = open(".HISTORY", O_RDONLY);
				tmp = all.tline.str;
				all.tline.str = get_hist_line(tline.curr_line, hist_fd);
				free (tmp);
				all.tline.cursor = ft_strlen(all.tline.str) + PROMPT;
				all.tline.symb_num = ft_strlen(all.tline.str) + PROMPT;
				count = ft_strlen(all.tline.str);
				if (tline.curr_line++ < tline.line_num)
					write(1, all.tline.str, ft_strlen(all.tline.str));
				else
					write(1, all.tline.str, ft_strlen(all.tline.str));
				close(hist_fd);
			}
			else if (!strcmp(str, key_backspace) || !strcmp(str, "\177"))
			{	
				if (all.tline.cursor > PROMPT)
				{
					all.tline.cursor--;
					all.tline.symb_num--;
					ft_putstr_fd(cursor_left, 1);
					ft_putstr_fd(tgetstr("dc", 0), 1);
				}
			}
			else if (!strcmp(str, LEFT))
			{
				if (all.tline.cursor > PROMPT)
				{
					all.tline.cursor--;
					ft_putstr_fd(tgetstr("le", 0), 1);
				}
			}
			else if (!strcmp(str, RiGHT))
			{
				if (all.tline.symb_num > all.tline.cursor)
				{
					all.tline.cursor++;
					ft_putstr_fd(tgetstr("nd", 0), 1);
				}
			}
			else
			{
				all.tline.cursor += write(1, str, l);
				all.tline.str[count] = str[0];
				all.tline.str[count + 1] = 0;
				count++;
			}
		}
		printf("%d\n", (int)all.tline.str[count]);
		if (all.tline.str[0] != '\n')
			write(fd, all.tline.str, ft_strlen(all.tline.str));
		all.tline.str[count - 1] = 0;
		free(all.tline.str);
		tline.line_num++;
		// parser(all.tline.str, &all);
	}
	// execute(&all);
	buildin_func(&all, argv, envp);
	write(1, "\n", 1);
	// close (fd);
	free (str);
	free_hisr_arr(&all);
	return (0);
}