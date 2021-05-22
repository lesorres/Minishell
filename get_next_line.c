/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhyman <fhyman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 22:15:00 by fhyman            #+#    #+#             */
/*   Updated: 2021/05/21 23:18:03 by fhyman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			result(int res, char **remainder, char **buf, char **tmp)
{
	free(*tmp);
	free(*buf);
	if (res == 0)
	{
		if (remainder)
		{
			free(*remainder);
			*remainder = NULL;
		}
		return (0);
	}
	return (1);
}

int			get_next_line(int fd, char **line)
{
	static char		*remainder;
	char			*buf;
	int				res;
	char			*tmp;

	res = 1;
	buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (fd < 0 || !buf || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0 || !line)
	{
		free(buf);
		return (-1);
	}
	while ((search_n(remainder)) == -1 && res > 0)
	{
		res = read(fd, buf, BUFFER_SIZE);
		buf[res] = '\0';
		tmp = remainder;
		remainder = ft_strjoin(remainder, buf);
		free(tmp);
	}
	*line = ft_substr(remainder, 0, (search_n(remainder)));
	tmp = remainder;
	remainder = ft_substr(remainder, search_n(remainder) + 1,
				ft_strlen(remainder));
	return (result(res, &remainder, &buf, &tmp));
}

// int   main(int ac, char **av)
// {
//   char  *line;
//   int   fd1;
//   int   fd2;

//   fd1 = open(av[1], O_RDONLY);
//   fd2 = open(av[2], O_RDONLY);
//   get_next_line(fd1, &line);
//   printf("%s\n", line);
//   get_next_line(fd1, &line);
//   printf("%s\n", line);
//   get_next_line(fd2, &line);
//   printf("%s\n", line);
//   get_next_line(fd2, &line);
//   printf("%s\n", line);
//   get_next_line(fd1, &line);
//   printf("%s\n", line);
//   get_next_line(fd2, &line);
//   printf("%s\n", line);
//   get_next_line(fd1, &line);
//   printf("%s\n", line);
//   get_next_line(fd2, &line);
//   printf("%s\n", line);
//   return (0);
// }