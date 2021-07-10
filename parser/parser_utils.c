/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhyman <fhyman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 23:11:26 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/07/10 22:41:48 by fhyman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_arr(char ***arr)
{
	int	i;

	i = 0;
	while ((*arr)[i])
	{
		free((*arr)[i]);
		(*arr)[i++] = NULL;
	}
}

int	error(char *str, char c, char c2)
{
	if (c2 != '\0')
		printf("%s%c%c'\n", str, c, c2);
	else
		printf("%s%c'\n", str, c);
	return (1);
}

int	set_all_initial_params(t_all *all, int *i, int *j, int *n)
{
	char	*tmp;

	all->p_num = 0;
	*i = 0;
	*j = 0;
	*n = 0;
	all->redid_err = 0;
	all->set = 0;
	all->cmd_n = 1;
	tmp = all->line;
	all->line = ft_strtrim(all->line, " \t");
	free(tmp);
	if (check_line_validity(all->line) == 1)
		return (1);
	all->line_len = ft_strlen(all->line);
	all->cmd = NULL;
	cmd_mem_alloc(all);
	return (0);
}

int	check_line_validity(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if ((line[i] == ';' && line[i + 1] == ';')
			|| (line[i] == '|' && line[i + 1] == '|'))
			return (error("syntax error near unexpected token `",
					line[i], line[i]));
		if (ft_strchr(";|", line[0]))
			return (error("syntax error near unexpected token `",
					line[0], '\0'));
		if (ft_strchr(";|", line[i]))
		{
			i++;
			while (line[i] && line[i] == ' ')
				i++;
			if (line[i] && ft_strchr(";|", line[i]))
				return (error("syntax error near unexpected token `",
						line[i], '\0'));
		}
		i++;
	}
	return (0);
}

void	semicolon_or_pipe(t_all *all)
{
	if (all->p_num == 0)
	{
		all->cmd_i = all->cmd_n - 2;
		buildin_func(all);
	}
	else
	{
		all->cmd_i = all->cmd_n - 2 - all->p_num;
		pipe_exec(all);
	}
	all->p_num = 0;
}
