/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhyman <fhyman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 16:04:37 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/07/10 22:44:10 by fhyman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clean_echo_from_flags(t_all *all, int i, int j)
{
	char	**tmp;
	int		k;
	int		t;
	int		g;

	g = i;
	k = 1;
	all->cmd[j].echo_n = 1;
	tmp = calloc(all->cmd[j].arg_n, sizeof(char *));
	tmp[0] = all->cmd[j].arg[0];
	while (all->cmd[j].arg[i])
		tmp[k++] = all->cmd[j].arg[i++];
	t = 1;
	while (t < g)
	{
		free(all->cmd[j].arg[t]);
		t++;
	}
	free(all->cmd[j].arg);
	all->cmd[j].arg = tmp;
}

void	check_echo_n_flag(t_all *all, int j)
{
	int	i;
	int	k;

	if (!ft_strcmp(all->cmd[j].arg[0], "echo"))
	{
		i = 1;
		while (all->cmd[j].arg[i] && !ft_strncmp(all->cmd[j].arg[i], "-n", 2))
		{
			k = 2;
			while (all->cmd[j].arg[i][k] == 'n')
				k++;
			if (all->cmd[j].arg[i][k])
				break ;
			else
				i++;
		}
		if (i == 1)
			return ;
		else
			clean_echo_from_flags(all, i, j);
	}
	i = 0;
}

int	extract_tokens(t_all *all, int i, int *j, int *k)
{
	while (all->line[i] != ' ' && all->line[i])
	{
		if (all->line[i] == ';' || all->line[i] == '|')
		{
			i++;
			break ;
		}
		else
		{
			all->set = 1;
			i = process_quotes(all, i, k, *j);
			if (all->line[i] != ' ' && all->line[i] != ';'
				&& all->line[i] != '|' && all->line[i])
			{
				if (all->line[i] == '$')
					process_dollar_sign(all, &i, k);
				else if (all->line[i] == '>' || all->line[i] == '<')
					i = process_redirections(all, i, *j, all->line_len);
				else
					(all->tmp)[(*k)++] = all->line[i++];
			}
		}
	}
	(all->tmp)[(*k)] = '\0';
	return (i);
}

void	write_tokens_to_cmd_and_process(t_all *all, int i, int *j, int *n)
{
	if (all->set == 1)
	{
		arr_mem_alloc(all, (*j));
		all->cmd[(*j)].arg[(*n)] = malloc(ft_strlen(all->tmp) + 1);
		ft_strcpy(all->cmd[(*j)].arg[(*n)], all->tmp);
		(*n)++;
	}
	all->set = 0;
	if (all->line[i - 1] == ';')
	{
		check_echo_n_flag(all, (*j));
		semicolon_or_pipe(all);
		(*j)++;
		cmd_mem_alloc(all);
		(*n) = 0;
	}
	if (all->line[i - 1] == '|')
	{
		check_echo_n_flag(all, (*j));
		(*j)++;
		cmd_mem_alloc(all);
		(*n) = 0;
		all->p_num++;
	}
	free(all->tmp);
}

void	parser(t_all *all, char **arg, char **envp)
{
	int	i;
	int	j;
	int	n;
	int	k;

	all->arg = arg;
	all->envp = envp;
	if (set_all_initial_params(all, &i, &j, &n))
		return ;
	while (all->line[i])
	{
		k = 0;
		all->tmp = ft_calloc(all->line_len + 1, sizeof(char));
		i = skip_spaces(all, i);
		i = extract_tokens(all, i, &j, &k);
		if (check_redir_err(all))
			return ;
		write_tokens_to_cmd_and_process(all, i, &j, &n);
	}
	if (!all->cmd[j].null && all->cmd[j].arg)
	{
		check_echo_n_flag(all, j);
		semicolon_or_pipe(all);
	}
}
