/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 21:53:27 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/04/25 13:46:46 by kmeeseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*ss;
	char	cc;
	int		i;

	ss = (char *)s;
	cc = (char)c;
	i = 0;
	while (*ss != '\0')
	{
		if (*ss == c)
			return (ss);
		ss++;
	}
	if (*ss == '\0' && cc == '\0')
		return (ss);
	return (NULL);
}
