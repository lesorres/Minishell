#include "libft.h"
#include <stdio.h>

int	len_arr(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	i += 1;
	return (i);
}

void	add_new_line_to_arr(char ***arr, char *line)
{
	char	**new_arr;
	int		i;
	char	*tmp;

	i = len_arr(*arr);
	new_arr = calloc((i + 1), sizeof(char *));
	if (!new_arr)
		write(1, "error", 5);
	new_arr[i] = NULL;
	tmp = ft_strdup(line);
	new_arr[--i] = tmp;
	while (i--)
		new_arr[i] = (*arr)[i];
	free(*arr);
	*arr = new_arr;
}
