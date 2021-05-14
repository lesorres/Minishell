#include "minishell.h"

// -ltermcap использовать при компиляции в makefile
// gcc main1.c minishell.h ft_strcmp.c -ltermcap ./libft_ash/ft_putstr_fd.c 

char	*ft_realloc(char *ptr, unsigned int size)
{
	char			*new;
	unsigned int	i;
	new = (char*)malloc(size * sizeof(char));
	i = 0;
	while (i < size && ptr[i] != '\0')
	{
		new[i] = ptr[i];
		i++;
	}
	free(ptr);
	return (new);
}

char	*read_line(int fd)
{
	int     ret;
	char    *buf;
	int     i;
	int		num;

	num = 1;
	buf = (char *)malloc(num);
	ret = 1;
	i = 0;
	while (ret > 0)
	{
		ret = read(fd, &buf[i], 1);
		if (buf[i] != '\n' && ret > 0)
		{
			buf = ft_realloc(buf, ++num);
			// printf("%c", buf[i]);
			i++;
		}
	}
	buf[i] = '\0';
	return (buf);
}

// int main(int argc, char **argv)
// {
// 	int fd = 0;

// 	// fd = open(argv[1], O_RDONLY);
// 	// read_line(fd);
// 	printf("%s\n", read_line(fd));
// 	return (0);
// }