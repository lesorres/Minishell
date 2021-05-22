#include "minishell.h"

int	count_hist_lines(int fd)
{
	int		i;
	int		k;
	int		file;
	char	*str;

	i = 0;
	k = 0;
	while (file == read(fd, str, 1) > 0)
	{
		if (str[i] == '\n')
			k++;
	}
	if (file == -1)
		return (-1);
	return (k);
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
    // all->hist_arr[0] = ft_strdup("");
}

void	rewrite_hist(t_all *all, char *line)
{
	int	fd;

	fd = open(".HISTORY", O_RDWR | O_CREAT | O_APPEND, 0777);
	ft_putendl_fd(line, fd);
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

// int main()
// {
//     t_all all;
//     char    *line;

    
//     init_all(&all);
//     init_hist(&all);
    
//     line = ft_strdup("history");
//     rewrite_hist(&all, line);
//     line = ft_strdup("second line");
//     rewrite_hist(&all, line);
//     printf("%s\n", all.hist_arr[0]);
//     printf("%s\n", all.hist_arr[1]);
//     return (0);
// }