/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 17:30:45 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/07/01 22:17:33 by kmeeseek         ###   ########.fr       */
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
		all->cmd[j].i_rdir = open(file_name, O_WRONLY | O_CREAT, 0644);
	}
	else if (all->line[i] == '<')
	{
		i++;
		i = skip_spaces(all, i);
		while (!ft_strchr(" ;|<>\0", all->line[i]))
			file_name[n++] = all->line[i++];
		file_name[n] = '\0';
		all->cmd[j].i_rdir = open(file_name, O_WRONLY, 0644);
	}
	// printf ("o_rdir in p_redir = %i\n", all->cmd[j].o_rdir);
	free(file_name);
	all->set = 0;
	return (i);
}