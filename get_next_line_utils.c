/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhyman <fhyman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 22:15:22 by fhyman            #+#    #+#             */
/*   Updated: 2021/01/13 17:54:21 by fhyman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			search_n(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

size_t		ft_strlen(const char *str)
{
	int			i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	size_t	k;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		s1 = "";
	k = 0;
	if (!(s3 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	while (*s1)
		s3[k++] = *s1++;
	while (*s2)
		s3[k++] = *s2++;
	s3[k] = '\0';
	return (s3);
}

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;
	size_t	k;

	k = start;
	new = NULL;
	if (!s)
		return (NULL);
	i = -1;
	if (start > ft_strlen(s))
		new[0] = '\0';
	while (k < len && s[k])
		k++;
	if (!(new = malloc(sizeof(char) * (k + 1))))
		return (NULL);
	while (++i < len && s[start])
		new[i] = s[start++];
	new[i] = '\0';
	return (new);
}
