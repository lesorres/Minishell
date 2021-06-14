#include "libft.h"
#include <stdio.h>

int len_arr(char **str)
{
    int	i;

	i = 0;
	while (str && str[i])
		i++;
    i += 1;
	return (i);
}

void    add_new_line_to_arr(char ***arr, char *line)
{
	char	**new_arr;
	int		i;
	char	*tmp;

		// i = 0;
		// while ((*arr)[i])
		// {
		// 	printf("all->path_arr[%i] = %s\n", i, (*arr)[i]);
		// 	i++;
		// }

	i = len_arr(*arr);
	if(!(new_arr = calloc((i + 1), sizeof(char *))))
		write(1, "error", 5);
	new_arr[i] = NULL;
	tmp = ft_strdup(line);
	new_arr[--i] = tmp;
	while (i--)
	{
		new_arr[i] = (*arr)[i];
		// printf("new_arr[%i] = %s\n", i, new_arr[i]);
	}
	free(*arr);
	*arr = new_arr;
}
