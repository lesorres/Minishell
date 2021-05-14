/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 20:33:54 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/04/25 13:44:46 by kmeeseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_tabs(char **words, size_t i)
{
	while (i--)
	{
		if (&(words[i]) && *&(words[i]))
		{
			free(*&(words[i]));
			*&(words[i]) = NULL;
		}
	}
	free(words);
}

static int	lines(char const *s, char c)
{
	int	i;
	int	j;

	j = 0;
	i = -1;
	while (s[++i])
		if (s[i] != c && (s[i + 1] == c || !s[i + 1]))
			j++;
	return (j);
}

static int	tabs(char **res, char *t, char c)
{
	int		len_word;
	int		j;

	j = 0;
	while (*t)
	{
		len_word = 0;
		while (*(t + len_word) != c && *(t + len_word))
			++len_word;
		if (len_word > 0)
		{
			res[j] = ft_substr(t, 0, len_word);
			if (!res[j++])
			{
				free_tabs(res, j);
				return (0);
			}
			t = t + len_word - 1;
		}
		t++;
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	char	*t;
	int		count_word;

	if (!s)
		return (NULL);
	count_word = lines(s, c);
	t = (char *)s;
	res = (char **)malloc((count_word + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	res[count_word] = NULL;
	tabs(res, t, c);
	return (res);
}
