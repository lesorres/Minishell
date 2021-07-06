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

// static int len(char **str)
// {
//     int	i;

// 	i = 0;
// 	while (str && str[i])
// 		i++;
//     i += 1;
// 	return (i);
// }


// int add_last_line(char ***input, char *line)
// {
//     char    **out;
//     int     i;
    
//     i = len(*input);
//     if(!(out = (char**)calloc((i + 1), sizeof(char*))))  //malloc
//         return(0);
//     out[i] = NULL;
//     out[--i] = line;
//     while (i--)
//         out[i] = (*input)[i];
//     free(*input);
//     *input = out;
//     return(1);
// }

// char **create_arr(int i)
// {
//     char **out;

//     if (i < 1)
//         i = 1;
//     out = (char**)calloc(i, sizeof(char*));
//     while (i--)
//         out[i] = NULL;
//     return (out); 
// }


// void	rewrite_hist(t_all *all, char *line)
// {
// 	int	fd;

// 	fd = open(".HISTORY", O_RDWR | O_CREAT | O_APPEND, 0777);
// 	ft_putstr_fd(line, fd);
// 	close(fd);
// 	add_last_line(&all->hist_arr, line);
// }

// void	init_hist(t_all *all)
// {
// 	int	fd;
// 	char	*line;

// 	fd = open(".HISTORY", O_RDWR | O_CREAT | O_APPEND, 0777);
// 	line = NULL;
// 	get_next_line(fd, &line);
// 	while (*line)
// 	{
// 		// add_last_line(&all->hist_arr, line);
// 		get_next_line(fd, &line);
// 		free(line);
// 	}
// 	close(fd);
// }

// static int line_len(char *str)
// {
//     int	i;

// 	i = 0;
// 	while (str && str[i])
// 		i++;
// 	return (i);
// }

// void	free_hisr_arr(t_all *all)
// {
// 	int	i;
	
// 	i = 0;
// 	while (all->hist_arr[i])
// 	{
// 		free(all->hist_arr[i]);
// 		i++;
// 	}
// 	free (all->hist_arr);
// }

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

void	split_path(t_all *all)
{
	char	*tmp;
	char	*tmp_2;
	int		line_len;
	int		i;

	i = 0;
	while (all->tline.env_arr[i])
	{
		if (ft_strncmp(all->tline.env_arr[i], "PATH=", 5) == 0)
			break;
		i++;
	}
	if (all->tline.env_arr[i] == NULL)
		all->path_arr = NULL;
	else
	{
		line_len = ft_strlen(all->tline.env_arr[i]);
		tmp = ft_substr(all->tline.env_arr[i], 5, (line_len - 5));
		tmp_2 = ft_strtrim(tmp, "\'\"");
		free(tmp);
		all->path_arr = ft_split(tmp_2, ':');
		i = 0;
		while(all->path_arr[i])
		{
			line_len = ft_strlen(all->path_arr[i]) + 2;
			all->path_arr[i] = ft_realloc(all->path_arr[i], line_len);
			all->path_arr[i][line_len - 2] = '/';
			i++;
		}
		free(tmp_2);
	}
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

void	check_shlvl(t_all *all, char **envp)
{
	int		i;
	int		j;
	char	*value;
	int		num;
	char	*tmp;
	char	*num_ch;

	i = 0;
	while (all->tline.env_arr[i] && ft_strnstr(all->tline.env_arr[i], "SHLVL=", 6) == NULL)
		i++;
	if (all->tline.env_arr[i] && ft_strncmp(all->tline.env_arr[i], "SHLVL=", 6))
	{
		add_new_env_param(all, "SHLVL=1");
		all->tline.first_shlvl = 1;
		write(1, "111\n", 4);  // debug
//		while (1){}  // debug
	}
	else if (all->tline.env_arr[i])
	{
		// j = find_env_equal(all->tline.env_arr[i]);
		num = ft_strlen(all->tline.env_arr[i]) - 6;
		value = ft_substr(all->tline.env_arr[i], 6, num); //leak
		if (!isdigit_line(value))
			num = ft_atoi(value) + 1;
		else
			num = 1;
		num_ch = ft_itoa(num);  //leak
		tmp = ft_strjoin("SHLVL=", num_ch);
		// all->tline.env_arr[i] = ft_realloc(all->tline.env_arr[i], ft_strlen(tmp) + 1);
		// ft_strcpy(all->tline.env_arr[i], tmp);
		free (all->tline.env_arr[i]);
		free(num_ch); // new line
		free(value); // new line
		all->tline.env_arr[i] = tmp;
		write(1, "222\n", 4); // debug
//		while (1){} // debug
	}
}

void set_terminal(struct  termios *term)
{
	term->c_lflag &= ~(ECHO);
	term->c_lflag &= ~(ICANON);
	term->c_lflag &= ~(ISIG);
	tcsetattr(0, TCSANOW, term);
}

void res_terminal(struct  termios *term)
{
	term->c_lflag |= ECHO | ICANON | ISIG;
	tcsetattr(0, TCSANOW, term);
}

void	init_all_vars(t_all *all)
{
	// all->line = malloc(1024);
	// status = ft_calloc(4, sizeof(char));
	// all->status = status;
	// all->tline.print_line = malloc(1024);
	// all->tline.cursor = PROMPT;
	// all->tline.symb_num = PROMPT;
	// all->tline.curr_line = all->tline.line_num;
}

// char *ft_incert_char(char *all_line, char c, int cursor)
// {
// 	char	*end;
// 	int		i;

// 	i = 0;
// 	printf("all_line before = %s\n", all_line);
// 	end = malloc(ft_strlen(&all_line[cursor - PROMPT]) + 1);
// 	end = ft_strcpy(end, &all_line[cursor - PROMPT]);
// 	all_line[(cursor++) - PROMPT] = c;
// 	while(end[i])
// 		all_line[(cursor++) - PROMPT] = end[i++];
// 	free(end);
// 	printf("all_line after = %s\n", all_line);
// 	return(all_line);
// }

void __free_arr(char **arr) {
	int i = 0;
	while (arr[i]) {
		free(arr[i++]);
	}
	free(arr);
}

void __print_arr(char **arr) {
	printf("print\n");
	int i = 0;
	while (arr[i]) {
		printf("%s\n", arr[i++]);
	}
}

int main(int argc, char **arg, char **envp)
{
	t_cmd 	cmd;
	t_all	all;
	t_termline tline;
	t_lst	builds;
	char	*str;
	int     l;
	int		i;
	struct  termios term;
	int		count;
	int		k;
	int		fd;
	// char    *path;
	char	*file_name;

	// all = ft_calloc(1, sizeof(t_all));
	all.in = dup(STDIN_FILENO);
	all.out = dup(STDOUT_FILENO);
	// path = malloc(PATH_LEN + 1);
	// all.tline.path = getcwd(path, PATH_LEN);
	all.tline.path = NULL;
	all.tline.path = getcwd(all.tline.path, PATH_LEN);
	file_name = ft_strjoin(all.tline.path, "/.HISTORY");
	fd = open(file_name, O_RDWR | O_CREAT, 0777);
	tcgetattr(0, &term);
	tgetent(0, TERM_NAME);
	str = ft_calloc(10, sizeof(char));
	tline.line_num = hist_line_num(fd);
	all.status = 0;
	get_envp(&all, envp);
	// check_shlvl(&all, all.tline.env_arr);
	// init_all_vars(&all);
	status = 0;
	// split_path(&all);
	while (ft_strcmp(str, "\4"))
	{
		set_terminal(&term);
		// all.status = status;
		// printf("status = %s\n", status);
		all.line = malloc(1024);				//leak
		all.tline.print_line = malloc(1024); 	//leak - исправила с помощью free внизу
		all.tline.cursor = PROMPT;
		all.tline.symb_num = PROMPT;
		// all.tline.print_line = NULL;
		tline.curr_line = tline.line_num;
		write(1, "#minishell> ", PROMPT);
		ft_putstr_fd(save_cursor, 1);
		str[0] = 0;
		count = 0;
		while (ft_strcmp(str, "\n") && ft_strcmp(str, "\4"))
		{
			if (all.tline.symb_num < all.tline.cursor)
				all.tline.symb_num = all.tline.cursor;
			l = read(1, str, 10);
			str[l] = 0;
			if (!ft_strcmp(str, UP) || !ft_strcmp(str, OPT_UP) || !ft_strcmp(str, SHF_UP) || !ft_strcmp(str, CTRL_UP))
			{
				int		hist_fd;
				char	*tmp;

				ft_putstr_fd(restore_cursor, 1);
				ft_putstr_fd(tgetstr("ce", 0), 1);
				hist_fd = open(file_name, O_RDONLY);
				tmp = all.line;
				if (tline.curr_line > 0)
				{
					tline.curr_line--;
					all.line = get_hist_line(tline.curr_line, hist_fd);
					free (tmp);
					all.tline.cursor = ft_strlen(all.line) + PROMPT;
					all.tline.symb_num = ft_strlen(all.line) + PROMPT;
					count = ft_strlen(all.line);
					write(1, all.line, ft_strlen(all.line));
				}
				close(hist_fd);
			}
			else if (!ft_strcmp(str, DWN) || !ft_strcmp(str, OPT_DWN) || !ft_strcmp(str, SHF_DWN) || !ft_strcmp(str, CTRL_DWN))
			{
				int		hist_fd;
				char	*tmp;

				ft_putstr_fd(restore_cursor, 1);
				ft_putstr_fd(tgetstr("ce", 0), 1);
				hist_fd = open(file_name, O_RDONLY);
				tmp = all.line;
				if (tline.curr_line < tline.line_num && all.line[0] != '\n')
				{
					tline.curr_line++;
					all.line = get_hist_line(tline.curr_line, hist_fd);
					free (tmp);
					all.tline.cursor = ft_strlen(all.line) + PROMPT;
					all.tline.symb_num = ft_strlen(all.line) + PROMPT;
					count = ft_strlen(all.line);
					write(1, all.line, ft_strlen(all.line));
				}
				else if (tline.curr_line == tline.line_num)
				{
					write(1, all.tline.print_line, ft_strlen(all.tline.print_line));
					free(all.line); // new line
					all.line = ft_calloc(1024, sizeof(char));
					all.line = ft_strcpy(all.line, all.tline.print_line);
					count = ft_strlen(all.line);
				}
				close(hist_fd);
			}
			else if (!ft_strcmp(str, key_backspace) || !ft_strcmp(str, "\177"))
			{	
				if (all.tline.cursor > PROMPT)
				{
					all.tline.cursor--;
					all.tline.symb_num--;
					all.tline.print_line[count--] = '\0';
					ft_putstr_fd(cursor_left, 1);
					ft_putstr_fd(tgetstr("dc", 0), 1);
				}

			}
			else if (!ft_strcmp(str, LEFT))
			{
				if (all.tline.cursor > PROMPT)
				{
					all.tline.cursor--;
					ft_putstr_fd(tgetstr("le", 0), 1);
				}
			}
			else if (!ft_strcmp(str, RiGHT))
			{
				if (all.tline.symb_num > all.tline.cursor)
				{
					all.tline.cursor++;
					ft_putstr_fd(tgetstr("nd", 0), 1);
				}
			}
			else if (!ft_strcmp(str, "\003"))
			{
				write(1, "\n#minishell> ", PROMPT + 1);
				ft_putstr_fd(save_cursor, 1);
			}
			// else if (all.tline.symb_num > all.tline.cursor)
			// {
			// 	all.line = ft_incert_char(all.line, str[0], all.tline.cursor);
			// 	ft_putstr_fd(tgetstr("im", 0), 1);
			// 	all.tline.cursor += write(1, str, 1);
			// 	all.tline.symb_num++;
			// 	ft_putstr_fd(tgetstr("ei", 0), 1);
			// }
			else if (ft_isprint(str[0]) || str[0] == '\n')
			{
				// printf("count = %i\n", count);
				all.tline.cursor += write(1, str, l);
				all.tline.print_line[count] = str[0];
				all.tline.print_line[count + 1] = 0;
				all.line[count] = str[0];
				all.line[count + 1] = 0;
				count++;
			}
		}
		if (!ft_strcmp(str, "\4"))
		{
			write(1, "exit\n", 5);
			exit (0);
		}
		if (all.line[0] != '\n')
			write(fd, all.line, ft_strlen(all.line));
			// write(fd, all.tline.print_line, ft_strlen(all.tline.print_line));
		all.line[count - 1] = 0;
		all.tline.print_line[count - 1] = 0;
		res_terminal(&term);
		parser(&all, arg, envp);
//		__print_arr(all.cmd->arg);
		__free_arr(all.cmd->arg); // new
		// __free_arr(all.tline.env_arr); // new - были проблемы двойного очищения памяти
		free(all.line);  //проверить
		free(all.tline.print_line); //проверить
		tline.line_num++;
	}
	close(fd);
	write(1, "\n", 1);
	free (str);
	return (0);
}