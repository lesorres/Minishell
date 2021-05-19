/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 16:04:37 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/05/16 22:20:37 by kmeeseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

// gcc parser_main.c parcer.c minishell.h libft/libft.a

void	realloc_cmd(t_all *all)
{
	
}

 void 	first_mem_alloc(t_all *all)
 {
	int i;

	i = 0;
	all->cmd.cmd_num = 5;
	all->cmd.s_cmd = malloc(sizeof(t_s_cmd) * all->cmd.cmd_num);
	all->cmd.s_cmd[all->cmd.cmd_num] = NULL;
	while (i < all->cmd.cmd_num)
	{
		all->cmd.s_cmd[i]->arg = malloc(sizeof(char*) * all->cmd.cmd_num);
		all->cmd.s_cmd[i]->arg[all->cmd.cmd_num] = NULL;
		all->cmd.s_cmd[i]->redir = malloc(sizeof(char*) * all->cmd.cmd_num);
		all->cmd.s_cmd[i]->redir[all->cmd.cmd_num] = NULL;
		i++;
	}
 }

void	parser(char *line, t_all *all)
{
	int i;
	int j;
	int k;
	int n;

	i = 0;
	j = 0;
	k = 0;
	n = 0;
	line = ft_strtrim(line, " ");
	while(line[i])
	{
		if (all->cmd.s_cmd[j]->arg[n][k] == ' ')
		{
			n++;
			k = 0;
		}
		if (all->cmd.s_cmd[j]->arg[n][k] == ';')
		{
			j++;
			n = 0;
			k = 0;
		}
		all->cmd.s_cmd[j]->arg[n][k] = line[i];
		k++;
	}
}
// void insert_arg(char * arg);
