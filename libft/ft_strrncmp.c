#include "libft.h"

int	ft_strrncmp(char *s1, char *s2, size_t n)
{
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	while ((len1-- || len2--) && (len1 < n || len2 < n))
	{
		if (s1[len1] > s2[len2])
			return (1);
		if (s1[len1] < s2[len2])
			return (-1);
	}
	return (0);
}
