/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhyman <fhyman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 23:34:38 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/07/10 22:27:30 by fhyman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quotes_flags_switch(t_all *all, char *line, int i, int j)
{
	if (line[i] == '\'' && !all->cmd[j].sq_fl && !all->cmd[j].dq_fl)
	{
		all->cmd[j].sq_fl = 1;
		i++;
	}
	else if ((line[i] == '\"' && !all->cmd[j].dq_fl && !all->cmd[j].sq_fl))
	{
		all->cmd[j].dq_fl = 1;
		i++;
	}
	else if (line[i] == '\'' && all->cmd[j].sq_fl)
	{
		all->cmd[j].sq_fl = 0;
		i++;
	}
	else if (line[i] == '\"' && all->cmd[j].dq_fl)
	{
		all->cmd[j].dq_fl = 0;
		i++;
	}
	return (i);
}

int	process_quotes(t_all *all, int i, int *k, int j)
{
	while (all->line[i] == '\"' || all->line[i] == '\'')
	{
		while (all->line[i] == '\"')
			i = quotes_flags_switch(all, all->line, i, j);
		while (all->line[i] == '\'' && !all->cmd[j].dq_fl)
			i = quotes_flags_switch(all, all->line, i, j);
		while ((all->cmd[j].dq_fl || all->cmd[j].sq_fl) && all->line[i])
		{
			if (all->line[i] == '$' && all->cmd[j].dq_fl)
				process_dollar_sign(all, &i, k);
			else
				(all->tmp)[(*k)++] = all->line[i++];
			i = quotes_flags_switch(all, all->line, i, j);
		}
	}
	return (i);
}

void	print_err3(t_all *all, char *cmd, char *err_name)
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, err_name, ft_strlen(err_name));
	write(2, "\n", 1);
	all->redid_err = 1;
}

int	check_redir_err(t_all *all)
{
	if (all->redid_err == 1)
	{
		free (all->tmp);
		return (1);
	}
	return (0);
}
