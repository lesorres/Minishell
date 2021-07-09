/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 23:34:38 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/07/09 23:35:34 by kmeeseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
