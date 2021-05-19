/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 19:09:10 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/05/19 20:05:48 by kmeeseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*result;
	size_t			i;
	unsigned int	sizes;

	if (!s)
		return (0);
	sizes = ft_strlen(s);
	i = 0;
	if (sizes <= start)
	{
		len = 0;
		start = sizes;
	}
	result = malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (0);
	while (i < len && s[i + start] != '\0')
	{
		result[i] = s[i + start];
		i++;
	}
	result[i] = '\0';
	return (result);
}
