/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhyman <fhyman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 17:30:45 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/07/10 22:27:33 by fhyman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_spaces(t_all *all, int i)
{
	while (all->line[i] == ' ' || all->line[i] == '\t')
		i++;
	return (i);
}

int	skip_spaces_and_rewrite_func_name(t_all *all, int i, char **file_name)
{
	int	n;

	n = 0;
	i = skip_spaces(all, i);
	while (!ft_strchr(" ;|<>\0", all->line[i]))
		(*file_name)[n++] = all->line[i++];
	(*file_name)[n] = '\0';
	return (i);
}

int	process_write_redirections(t_all *all, int i, int j, int line_len)
{
	char	*file_name;

	file_name = ft_calloc(sizeof(char), line_len);
	if (all->line[i] == '>' && all->line[i + 1] == '>')
	{
		i = i + 2;
		i = skip_spaces_and_rewrite_func_name(all, i, &file_name);
		all->cmd[j].o_rdir = open(file_name, O_WRONLY
				| O_CREAT | O_APPEND, 0644);
		if (all->cmd[j].o_rdir == -1)
			print_err3(all, file_name, strerror(errno));
	}
	else if (all->line[i] == '>')
	{
		i++;
		i = skip_spaces_and_rewrite_func_name(all, i, &file_name);
		all->cmd[j].o_rdir = open(file_name, O_WRONLY
				| O_CREAT | O_TRUNC, 0644);
		if (all->cmd[j].o_rdir == -1)
			print_err3(all, file_name, strerror(errno));
	}
	free(file_name);
	return (i);
}

int	process_read_redirections(t_all *all, int i, int j, int line_len)
{
	char	*file_name;

	file_name = ft_calloc(sizeof(char), line_len);
	if (all->line[i] == '<' && all->line[i + 1] == '<')
	{
		i = i + 2;
		i = skip_spaces_and_rewrite_func_name(all, i, &file_name);
		all->cmd[j].i_rdir = open(file_name, O_RDONLY | O_CREAT, 0644);
		if (all->cmd[j].i_rdir == -1)
			print_err3(all, file_name, strerror(errno));
	}
	else if (all->line[i] == '<')
	{
		i++;
		i = skip_spaces_and_rewrite_func_name(all, i, &file_name);
		all->cmd[j].i_rdir = open(file_name, O_RDONLY, 0644);
		if (all->cmd[j].i_rdir == -1)
			print_err3(all, file_name, strerror(errno));
	}
	free(file_name);
	return (i);
}

int	process_redirections(t_all *all, int i, int j, int line_len)
{
	if (all->line[i] == '>')
		i = process_write_redirections(all, i, j, line_len);
	else if (all->line[i] == '<')
		i = process_read_redirections(all, i, j, line_len);
	if (!all->tmp[0])
		all->set = 0;
	return (i);
}
