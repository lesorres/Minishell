/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhyman <fhyman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 17:30:45 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/07/04 13:40:50 by fhyman           ###   ########.fr       */
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

	n = 0;
	file_name = ft_calloc(sizeof(char), line_len);
	// printf ("o_rdir in p_redir before dup = %i\n", all->cmd[j].o_rdir);
	if (all->line[i] == '>' && all->line[i + 1] == '>')
	{
		i = i + 2;
		i = skip_spaces(all, i);
		while (!ft_strchr(" ;|<>\0", all->line[i]))
			file_name[n++] = all->line[i++];
		file_name[n] = '\0';
		all->cmd[j].o_rdir = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (all->cmd[j].o_rdir == -1)
			print_err2(all->cmd[j].arg[0], strerror(errno));
	}
	else if (all->line[i] == '>')
	{
		i++;
		i = skip_spaces(all, i);
		while (!ft_strchr(" ;|<>\0", all->line[i]))
			file_name[n++] = all->line[i++];
		file_name[n] = '\0';
		all->cmd[j].o_rdir = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (all->cmd[j].o_rdir == -1)
			print_err2(all->cmd[j].arg[0], strerror(errno));
	}
	else if (all->line[i] == '<' && all->line[i + 1] == '<')
	{
		i = i + 2;
		i = skip_spaces(all, i);
		while (!ft_strchr(" ;|<>\0", all->line[i]))
			file_name[n++] = all->line[i++];
		file_name[n] = '\0';
		all->cmd[j].i_rdir = open(file_name, O_RDONLY | O_CREAT, 0644);
		if (all->cmd[j].i_rdir == -1)
			print_err2(all->cmd[j].arg[0], strerror(errno));
	}
	else if (all->line[i] == '<')
	{
		i++;
		i = skip_spaces(all, i);
		while (!ft_strchr(" ;|<>\0", all->line[i]))
			file_name[n++] = all->line[i++];
		file_name[n] = '\0';
		all->cmd[j].i_rdir = open(file_name, O_RDONLY, 0644);
		if (all->cmd[j].i_rdir == -1)
			print_err2(all->cmd[j].arg[0], strerror(errno));
	}
	// printf ("o_rdir in p_redir = %i\n", all->cmd[j].o_rdir);
	free(file_name);
	if (!all->tmp[0])
		all->set = 0;
	return (i);
}