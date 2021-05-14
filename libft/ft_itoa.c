/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 20:39:31 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/04/25 14:44:36 by kmeeseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*write_to_str(int n, int ngt, char *str)
{
	while (n)
	{
		if (ngt)
			*str-- = (n % 10) * -1 + 48;
		else
			*str-- = (n % 10) + 48;
		n = n / 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	int		temp;
	int		len;
	int		ngt;
	char	*str;

	temp = n;
	len = 1;
	ngt = n < 0;
	temp = temp / 10;
	while (temp)
	{
		temp = temp / 10;
		len++;
	}
	str = (char *)malloc(sizeof(*str) * (len + ngt + 1));
	if (!(str))
		return (NULL);
	if (ngt)
		*str++ = '-';
	str = str + len;
	*str-- = '\0';
	if (n == 0)
		*str-- = '0';
	str = write_to_str(n, ngt, str);
	return (str + 1 - ngt);
}
