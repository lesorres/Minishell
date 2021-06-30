/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_mem_alloc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 22:31:05 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/06/30 22:33:00 by kmeeseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	arr_mem_alloc(t_all *all, int j)
{
	int		i;
	int		old_arg_n;
	char	**tmp;

	i = 0;
	old_arg_n = all->cmd[j].arg_n;
	all->cmd[j].arg_n = all->cmd[j].arg_n + 1;
	if (!all->cmd[j].arg)
	{
		all->cmd[j].arg = ft_calloc(all->cmd[j].arg_n, sizeof(char *)); //не забудь проверку на NULL
	}
	else
	{
		tmp = ft_calloc(all->cmd[j].arg_n, sizeof(char *)); //не забудь проверку на NULL
		while (i < old_arg_n)
		{
			tmp[i] = all->cmd[j].arg[i];
			i++;
		}
		// сделать free all->cmd[j].arg и всех существующих строк
		all->cmd[j].arg = tmp;
		// free(tmp);
	}
}

void	cmd_mem_alloc(t_all *all)
{
	int i;
	int old_cmd_n;
	t_cmd *tmp;

	i = 0;
	old_cmd_n = all->cmd_n - 1;
	all->cmd_n = all->cmd_n + 1;
	if (!all->cmd)
	{
		all->cmd = ft_calloc(all->cmd_n, sizeof(t_cmd)); //не забудь проверку на NULL
			all->cmd[0].arg_n = 1;
			all->cmd[1].null = 1;
			all->cmd[0].o_rdir = 1; // NEW
	}
	else
	{
		tmp = ft_calloc(all->cmd_n, sizeof(t_cmd)); //не забудь проверку на NULL
		while (i < old_cmd_n)
		{
			tmp[i].arg_n = all->cmd[i].arg_n; //ДРУГИЕ ЭЛЕМЕНТЫ ДОБАВЬ
			tmp[i].arg = all->cmd[i].arg;
			// tmp[i].name = all->cmd[i].name;
			i++;
		}
		// if (all->cmd)
		// 	free(all->cmd);
		all->cmd = tmp;
		all->cmd[old_cmd_n].arg_n = 1;
		all->cmd[all->cmd_n - 1].null = 1;
		all->cmd[old_cmd_n].null = 0;
		all->cmd[old_cmd_n].o_rdir = 1; // NEW
	}
}