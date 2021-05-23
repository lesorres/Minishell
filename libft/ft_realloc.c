#include "libft.h"

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