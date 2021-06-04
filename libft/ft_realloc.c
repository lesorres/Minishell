#include "libft.h"

char	*ft_realloc(char *ptr, unsigned int size)
{
	char			*new;
	unsigned int	i;

	i = 0;
	new = (char*)malloc(size * sizeof(char));
	while (i < size && ptr[i] != '\0')
	{
		new[i] = ptr[i];
		i++;
	}
	free(ptr);
	return (new);
}