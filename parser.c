/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 16:04:37 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/06/06 19:28:37 by kmeeseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void free_arr(char ***arr)
{
	int	i;
	
	i = 0;
	while ((*arr)[i])
	{
		free((*arr)[i]);
		(*arr)[i++] = NULL;
	}
}

void print_parsed_string(t_all *all)
{
	int n = 0;
	int j = 0;
	while (!all->cmd[j].null && all->cmd[j].arg)
	{
		printf("name(#%i _)  = |%s|\n\n", j, all->cmd[j].name);
		while (all->cmd[j].arg[n])
		{
			// printf("adr       = |%p|\n", all->cmd[j].arg[n]);
			printf("str(#%i %i) = |%s|\n\n", j, n, all->cmd[j].arg[n]);
			// printf("%i - %i\n", n, all->cmd[j].arg_n);
			n++;
		}
		printf("arg_n = %i\n", all->cmd[j].arg_n);
		j++;
		n = 0;
	}
	printf("cmd_n = %i", all->cmd_n);
}

void error(char *str)
{
	printf("%s\n", str);
	exit(1);
}
void 	arr_mem_alloc(t_all *all, int j)
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

void 	cmd_mem_alloc(t_all *all)
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
	}
	else
	{
		tmp = ft_calloc(all->cmd_n, sizeof(t_cmd)); //не забудь проверку на NULL
		while (i < old_cmd_n)
		{
			tmp[i].arg_n = all->cmd[i].arg_n;
			tmp[i].arg = all->cmd[i].arg;
			i++;
		}
		// if (all->cmd)
		// 	free(all->cmd);
		all->cmd = tmp;
		all->cmd[old_cmd_n].arg_n = 1;
		all->cmd[all->cmd_n - 1].null = 1;
		all->cmd[old_cmd_n].null = 0;
	}
}

void extract_cmd_name(t_all *all) //утечек нет (вроде бы)
{
	int		j;
	int		i;
	char	**tmp;

	j = 0;
	while (!all->cmd[j].null && all->cmd[j].arg)
	{
		i = 0;
		all->cmd[j].name = all->cmd[j].arg[0];
		tmp = ft_calloc((all->cmd[j].arg_n - 1), sizeof(char *));
		while (all->cmd[j].arg[i + 1])
		{
			tmp[i] = all->cmd[j].arg[i + 1];
			i++;
		}
		free(all->cmd[j].arg);
		all->cmd[j].arg = tmp;
		j++;
	}
}

int		quotes_flags_switch(t_all *all, char *line, int i, int j)
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
	return	(i);
}

// int	check_quotes(t_all *all, char *line, int i, int j, int k)
// {
// 	i = quotes_flags_switch(all, line, i, j);
// 	if (all->cmd[j] = )
// }

void	parser(char *line, t_all *all)
{
	int i;					//счетчик line
	int j;					//номер команды
	int k;					//счетчик tmp
	int n;					//номер аргумента
	int	line_len;
	char *tmp;

	i = 0;
	j = 0;
	n = 0;
	all->cmd_n = 1;
	line = ft_strtrim(line, " ");
	line_len = ft_strlen(line);
	cmd_mem_alloc(all);
	while(line[i])
	{
		k = 0;
		tmp = malloc(line_len);
		while (line[i] == ' ') // && !all->cmd[j].dq_fl && !all->cmd[j].sq_fl)
			i++;
		while (line[i] != ' ' && line[i]) // && !all->cmd[j].dq_fl && !all->cmd[j].sq_fl)
		{
			if (line[i] == ';') // || line[i] == '|')
			{
				i++;
				break;
			}
			else
			{
				i = quotes_flags_switch(all, line, i, j);
				while ((all->cmd[j].dq_fl || all->cmd[j].sq_fl) && line[i])
				{
					tmp[k++] = line[i++];
					i = quotes_flags_switch(all, line, i, j);
				}
				if (line[i] != ' ' && line[i])
					tmp[k++] = line[i++];
			}
		}
		tmp[k] = '\0';
		if (tmp[0]) //здесь записываем слова в массив
		{
			arr_mem_alloc(all, j);
			all->cmd[j].arg[n] = malloc(ft_strlen(tmp));
			ft_strcpy(all->cmd[j].arg[n], tmp);
			n++;
			// all->cmd->arg_n = n;
		}
		if (line[i - 1] == ';')// && !all->cmd[j].dq_fl && !all->cmd[j].sq_fl)
		{
			if (line[i] == ';')
				error("syntax error near unexpected token `;;'");
			if (all->cmd[j].arg == NULL)
				error("syntax error near unexpected token `;'");
			j++;
			cmd_mem_alloc(all);
			n = 0;
			
		}
		free(tmp);
	}
	extract_cmd_name(all);
	print_parsed_string(all);
}
