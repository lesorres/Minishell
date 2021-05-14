/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 23:52:43 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/04/25 13:47:33 by kmeeseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	i;
	size_t	n;

	if (!s1 || !s2)
		return (0);
	i = 0;
	n = 0;
	result = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(*result));
	if (result == NULL)
		return (0);
	while (i != ft_strlen(s1))
	{
		result[i] = s1[i];
		i++;
	}
	while (i != (ft_strlen(s1) + ft_strlen(s2)))
	{
		result[i] = s2[n];
		i++;
		n++;
	}
	result[i] = '\0';
	return (result);
}
