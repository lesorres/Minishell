/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 16:36:53 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/04/25 13:35:01 by kmeeseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *restrict dst, const void *restrict src, \
int c, size_t n)
{
	size_t			i;
	unsigned char	*csrc;
	unsigned char	*cdst;
	unsigned char	cc;

	cc = (unsigned char)c;
	csrc = (unsigned char *)src;
	cdst = (unsigned char *)dst;
	i = 0;
	while (i != n)
	{
		cdst[i] = csrc[i];
		if (csrc[i] == cc)
		{
			cdst = cdst + i + 1;
			return (cdst);
		}
		i++;
	}
	return (NULL);
}
