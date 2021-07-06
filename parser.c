/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 16:04:37 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/07/07 00:18:26 by kmeeseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	print_parsed_string(t_all *all)
{
	int	n;
	int	j;

	n = 0;
	j = 0;
	while (!all->cmd[j].null && all->cmd[j].arg)
	{
		// printf("\nname(#%i _)  = |%s|\n\n", j, all->cmd[j].name);
		// printf("del(#%i %i) = |%d|\n", j, n, all->cmd[j].delim);
		while (all->cmd[j].arg[n])
		{
			// printf("adr       = |%p|\n", all->cmd[j].arg[n]);
			printf("str(#%i %i) = |%s|\n", j, n, all->cmd[j].arg[n]);
			// printf("%i - %i\n", n, all->cmd[j].arg_n);
			n++;
		}
		// printf("arg_n = %i\n", all->cmd[j].arg_n);
		printf("all.cmd_n = %i\n", all->cmd_n);
		printf("\n");
		j++;
		n = 0;
	}
}

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

int	error(char *str, char c, char c2)
{
	if (c2 != '\0')
		printf("%s%c%c'\n", str, c, c2);
	else
		printf("%s%c'\n", str, c);
	return (1);
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

void	clean_echo_from_flags(t_all *all, int i, int j) //ликов быть не должно
{
	char	**tmp;
	int		k;
	int		t;
	int		g;

	g = i;
	k = 1;
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

void	check_echo_n_flag(t_all *all, int j) // ЕСТЬ ЛИКИ
{
	int	i;
	int	k;
	int	flag;

	if (!ft_strcmp(all->cmd[j].arg[0], "echo")) //&& all->cmd[j].arg[1])
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
		{
			all->cmd[j].echo_n = 1;
			clean_echo_from_flags(all, i, j);
		}
	}
	i = 0;
}

void	process_dollar_sign(t_all *all, int *i, int *k)
{
	int		z;					//счетчик для печати status
	int		val_len;
	char	*loc_stat;

	loc_stat = ft_itoa(status);
	if (all->line[*i] == '$' && all->line[*i + 1] == '?')
	{
		*i = *i + 2;
		z = 0;
		while (loc_stat[z])
			all->tmp[(*k)++] = loc_stat[z++];
	}
	else if (all->line[*i] == '$' && 47 < all->line[*i + 1]
			&& all->line[*i + 1] < 58)
		*i = *i + 2;
	else if (all->line[*i] == '$')
	{
		val_len = compare_with_env(all, all->line, *i);
		all->tmp = ft_realloc(all->tmp, ft_strlen(all->line));
		while (all->line[*i] && val_len > 0)
		{
			all->tmp[(*k)++] = all->line[(*i)++];
			val_len--;
		}
	}
	free(loc_stat);
}

//вместо функции выше было:
					// if (all->line[i] == '$' && all->line[i + 1] == '?')
					// {
					// 	i = i + 2;
					// 	z = 0;
					// 	while (all->status[z])
					// 		tmp[k++] = all->status[z++];
					// }
					// else if (all->line[i] == '$')
					// {
					// 	// check_question_sing(all->line[i]); //учесть $?
					// 	val_len = compare_with_env(all, all->line, i);
					// 	tmp = ft_realloc(tmp, ft_strlen(all->line));
					// 	while (all->line[i] && val_len > 0)
					// 	{
					// 		tmp[k++] = all->line[i++];
					// 		val_len--;
					// 	}
					// }

void	semicolon_or_pipe(t_all *all, char **arg, char **envp)
{
	int	i;

	if (all->p_num == 0)
	{
		all->cmd_i = all->cmd_n - 2;
		buildin_func(all, arg, envp);
	}
	else
	{
		all->cmd_i = all->cmd_n - 2 - all->p_num;
		// printf ("o_rdir in semicolon or pipe= %i\n", all->cmd[0].o_rdir);
		pipe_exec(all, arg, envp);
	}
	all->p_num = 0;
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

// void	parser(t_all *all)
void	parser(t_all *all, char **arg, char **envp)
{
	int	i;					//счетчик line
	int	j;					//номер команды
	int	n;					//номер аргумента
	int	k;					//счетчик tmp
	int	line_len;

	all->p_num = 0;
	i = 0;
	j = 0;
	n = 0;
	all->set = 0;
	all->cmd_n = 1;
	char * tmp = all->line;
	all->line = ft_strtrim(all->line, " \t");
	free(tmp);//==========
	if (check_line_validity(all->line) == 1)
		return ;
	line_len = ft_strlen(all->line);
	all->cmd = NULL;
	cmd_mem_alloc(all);
	while (all->line[i])
	{
		k = 0;
		all->tmp = ft_calloc(line_len + 1, sizeof(char));
		i = skip_spaces(all, i);
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
				i = process_quotes(all, i, &k, j);
				if (all->line[i] != ' ' && all->line[i] != ';'
					&& all->line[i] != '|' && all->line[i])
				{
					if (all->line[i] == '$')
						process_dollar_sign(all, &i, &k);
					else if (all->line[i] == '>' || all->line[i] == '<')
						i = process_redirections(all, i, j, line_len);
					else
						(all->tmp)[k++] = all->line[i++];
				}
			}
		}
		(all->tmp)[k] = '\0';
		if (all->set == 1) //здесь записываем слова в массив  //убрала для кейса echo """"""""""       :"" хз не сломалось ли что еще 
		{
			arr_mem_alloc(all, j);
			all->cmd[j].arg[n] = malloc(ft_strlen(all->tmp) + 1);
			ft_strcpy(all->cmd[j].arg[n], all->tmp);
			n++;
		}
		all->set = 0;
		if (all->line[i - 1] == ';')
		{
			check_echo_n_flag(all, j);
			semicolon_or_pipe(all, arg, envp);
			j++;
			cmd_mem_alloc(all);
			n = 0;
		}
		if (all->line[i - 1] == '|')
		{
			check_echo_n_flag(all, j);
			j++;
			cmd_mem_alloc(all);
			n = 0;
			all->p_num++;
		}
		free(all->tmp);
	}
	//последняя команда не попадает под условие if (line[i - 1] == ';')
	if (!all->cmd[j].null && all->cmd[j].arg)
	{
		check_echo_n_flag(all, j);
		semicolon_or_pipe(all, arg, envp);
	}
	print_parsed_string(all);
}