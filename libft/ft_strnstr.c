/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 21:06:21 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/04/25 13:49:51 by kmeeseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	if (haystack == NULL && needle == NULL)
		return (0);
	if (!needle[i])
		return ((char *)haystack);
	while (haystack && haystack[i] && i < len)
	{
		if (haystack[i] == needle[n])
		{
			if (needle[n + 1] == '\0')
				return ((char *)haystack + i - n);
			i++;
			n++;
		}
		else
		{
			i = i - n + 1;
			n = 0;
		}
	}
	return (NULL);
}
