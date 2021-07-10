#include "libft.h"

int	ft_strchr_int(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (c == str[i])
		return (i);
	else
		return (-1);
}
