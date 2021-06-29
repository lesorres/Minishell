/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhyman <fhyman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 17:30:45 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/06/29 22:11:27 by fhyman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int skip_spaces(t_all *all, int i)
{
	while (all->line[i] == ' ' || all->line[i] == '\t') //запихнуть в отдельную функцию, также используется в parser.c
		i++;
	return(i);
}

int	process_redirections(t_all *all, int i, int j, int line_len)
{
	char	*file_name;
	int		n;
	int		tmp_fd;

	printf("i_rdir = %i\n", all->cmd[j].i_rdir);
	printf("o_rdir = %i\n", all->cmd[j].o_rdir);
	n = 0;
	file_name = ft_calloc(sizeof(char), line_len);
	if (all->line[i] == '>' && all->line[i + 1] == '>')
	{
		i = i + 2;
		i = skip_spaces(all, i);
		while (!ft_strchr(" ;|<>\0", all->line[i]))
			file_name[n++] = all->line[i++];
		file_name[n] = '\0';
		all->cmd[j].o_rdir = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else if (all->line[i] == '>')
	{
		i++;
		i = skip_spaces(all, i);
		while (!ft_strchr(" ;|<>\0", all->line[i]))
			file_name[n++] = all->line[i++];
		file_name[n] = '\0';
		all->cmd[j].o_rdir = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if (all->line[i] == '<' && all->line[i + 1] == '<')
	{
		i = i + 2;
		i = skip_spaces(all, i);
		while (!ft_strchr(" ;|<>\0", all->line[i]))
			file_name[n++] = all->line[i++];
		file_name[n] = '\0';
		all->cmd[j].i_rdir = open(file_name, O_RDONLY | O_CREAT, 0644);
	}
	else if (all->line[i] == '<')
	{
		i++;
		i = skip_spaces(all, i);
		while (!ft_strchr(" ;|<>\0", all->line[i]))
			file_name[n++] = all->line[i++];
		file_name[n] = '\0';
		all->cmd[j].i_rdir = open(file_name, O_RDONLY, 0644);
	}
	free(file_name);
	printf("i_rdir after open = %i\n", all->cmd[j].i_rdir);
	printf("o_rdir after open = %i\n", all->cmd[j].o_rdir);
	return (i);
}