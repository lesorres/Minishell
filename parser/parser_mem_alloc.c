/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_mem_alloc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhyman <fhyman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 22:31:05 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/07/10 22:27:26 by fhyman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	arr_mem_alloc(t_all *all, int j)
{
	int		i;
	int		old_arg_n;
	char	**tmp;

	i = 0;
	old_arg_n = all->cmd[j].arg_n;
	all->cmd[j].arg_n = all->cmd[j].arg_n + 1;
	if (!all->cmd[j].arg)
		all->cmd[j].arg = ft_calloc(all->cmd[j].arg_n, sizeof(char *));
	else
	{
		tmp = ft_calloc(all->cmd[j].arg_n, sizeof(char *));
		while (i < old_arg_n)
		{
			tmp[i] = all->cmd[j].arg[i];
			i++;
		}
		free(all->cmd[j].arg);
		all->cmd[j].arg = tmp;
	}
}

void	fill_in_last_cmd(t_all *all, t_cmd *tmp, int old_cmd_n)
{
	all->cmd = tmp;
	all->cmd[old_cmd_n].arg_n = 1;
	all->cmd[all->cmd_n - 1].null = 1;
	all->cmd[old_cmd_n].null = 0;
	all->cmd[old_cmd_n].o_rdir = 1;
}

int	fill_in_new_cmd_arr(t_all *all, t_cmd *tmp, int i)
{
	tmp[i].arg_n = all->cmd[i].arg_n;
	tmp[i].arg = all->cmd[i].arg;
	tmp[i].o_rdir = all->cmd[i].o_rdir;
	tmp[i].i_rdir = all->cmd[i].i_rdir;
	i++;
	return (i);
}

void	cmd_mem_alloc(t_all *all)
{
	int		i;
	int		old_cmd_n;
	t_cmd	*tmp;

	i = 0;
	old_cmd_n = all->cmd_n - 1;
	all->cmd_n = all->cmd_n + 1;
	if (!all->cmd)
	{
		all->cmd = ft_calloc(all->cmd_n, sizeof(t_cmd));
		all->cmd[0].arg_n = 1;
		all->cmd[1].null = 1;
		all->cmd[0].o_rdir = 1;
	}
	else
	{
		tmp = ft_calloc(all->cmd_n, sizeof(t_cmd));
		while (i < old_cmd_n)
			i = fill_in_new_cmd_arr(all, tmp, i);
		free(all->cmd);
		fill_in_last_cmd(all, tmp, old_cmd_n);
	}
}
