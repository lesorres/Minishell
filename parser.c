/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 16:04:37 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/06/24 19:31:38 by kmeeseek         ###   ########.fr       */
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
		printf("\n");
		j++;
		n = 0;
	}
	// printf("cmd_n = %i", all->cmd_n);
}

void error(char *str)
{
	printf("%s\n", str);
	// exit(1);
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
	}
}

void extract_cmd_name(t_all *all, int j) //утечек нет (вроде бы)
{
	int		i;
	char	**tmp;

	if (!all->cmd[j].null && all->cmd[j].arg)
	{
		i = 0;
		all->cmd[j].name = all->cmd[j].arg[0];
		tmp = ft_calloc((all->cmd[j].arg_n - 1), sizeof(char *));
		while (all->cmd[j].arg[i + 1])
		{
			tmp[i] = all->cmd[j].arg[i + 1];
			i++;
		}
		free(all->cmd[j].arg); //free_arr? не должны зачищаться строки
		all->cmd[j].arg = tmp;
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

// void	check_qoutes_content(all, line, i, j)
// {
// 	if (all->cmd[j].dq_fl)
// 	{
		
// 	}
// }

int		check_line_validity(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ';' && line[i + 1] == ';')
		{
			error("syntax error near unexpected token `;;'");
			return(1);
		}
		if (line[0] == ';')
		{
			error("syntax error near unexpected token `;'");
			return(1);
		}
		if (line[i] == ';')
		{
			i++;
			while (line[i] && line[i] == ' ')
				i++;
			if (line[i] && line[i] == ';')
			{
				error("syntax error near unexpected token `;'");
				return(1);
			}
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
	int k;
	int flag;

	if (!ft_strcmp(all->cmd[j].arg[0], "echo")) //&& all->cmd[j].arg[1])
	{
		i = 1;
		while (all->cmd[j].arg[i] && !ft_strncmp(all->cmd[j].arg[i], "-n", 2))
		{
			k = 2;
			while (all->cmd[j].arg[i][k] == 'n')
				k++;
			if (all->cmd[j].arg[i][k])
				break;
			else
				i++;
		}
		if (i == 1)
			return;
		else
		{
			all->cmd[j].echo_n = 1;
			clean_echo_from_flags(all, i, j);
		}
	}
	i = 0;
}

void	process_dollar_sign(t_all *all, char **tmp, int *i, int *k)
{
	int z;					//счетчик для печати status
	int val_len;

	if (all->line[*i] == '$' && all->line[*i + 1] == '?')
	{
		*i = *i + 2;
		z = 0;
		while (status[z])
			(*tmp)[(*k)++] = status[z++];
	}
	else if (all->line[*i] == '$')
	{
		val_len = compare_with_env(all, all->line, *i);
		*tmp = ft_realloc(*tmp, ft_strlen(all->line));
		while (all->line[*i] && val_len > 0)
		{
			(*tmp)[(*k)++] = all->line[(*i)++];
			val_len--;
		}
	}
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

// void	parser(t_all *all)

void	semicolon_or_pipe(t_all *all, char **arg, char **envp)
{
	int i;

	if (all->p_num == 0)
		buildin_func(all, arg, envp);
	else
	{
		i = all->cmd_n - 2 - all->p_num;
		pipe_exec(all, arg, envp, i);
	}
	all->p_num = 0;
}

void	parser(t_all *all, char **arg, char **envp)
{
	int i;					//счетчик line
	int j;					//номер команды
	int n;					//номер аргумента
	int k;					//счетчик tmp
	int	d;					//разница между i
	// int z;				//счетчик для печати status
	int	line_len;
	char *tmp;
	// int val_len;

	all->p_num = 0;
	i = 0;
	j = 0;
	n = 0;
	d = 0;
	all->cmd_n = 1;
	all->line = ft_strtrim(all->line, " \t");
	if (check_line_validity(all->line) == 1)
		return;
	line_len = ft_strlen(all->line);
	cmd_mem_alloc(all);
	while(all->line[i])
	{
		k = 0;
		tmp = malloc(line_len);
		while (all->line[i] == ' ' || all->line[i] == '\t')
			i++;
		while (all->line[i] != ' ' && all->line[i])
		{
			if (all->line[i] == ';'|| all->line[i] == '|')
			{
				i++;
				break;
			}
			else
			{
				while (all->line[i] == '\"' || all->line[i] == '\'')
				{
					while (all->line[i] == '\"')
						i = quotes_flags_switch(all, all->line, i, j);
					while (all->line[i] == '\'' && !all->cmd[j].dq_fl)
						i = quotes_flags_switch(all, all->line, i, j);
					while ((all->cmd[j].dq_fl || all->cmd[j].sq_fl) && all->line[i])
					{
						// i = check_qoutes_content(all, all->line, i, j);
						if (all->line[i] == '$' && all->cmd[j].dq_fl)
							process_dollar_sign(all, &tmp, &i, &k);
						else
							tmp[k++] = all->line[i++];
						i = quotes_flags_switch(all, all->line, i, j);
					}
				}
				if (all->line[i] != ' ' && all->line[i] != ';' && all->line[i] != '|' && all->line[i])
				{
					if (all->line[i] == '$')
						process_dollar_sign(all, &tmp, &i, &k);
					else
						tmp[k++] = all->line[i++];
				}
			}
		}
		tmp[k] = '\0';
		if (tmp[0]) //здесь записываем слова в массив
		{
			arr_mem_alloc(all, j);
			all->cmd[j].arg[n] = malloc(ft_strlen(tmp) + 1);
			ft_strcpy(all->cmd[j].arg[n], tmp);
			n++;
		}
		if (all->line[i - 1] == ';')
		{
			// extract_cmd_name(all, j);
			check_echo_n_flag(all, j);
			// buildin_func(all, arg, envp); заменила на semicolon_or_pipe
			semicolon_or_pipe(all, arg, envp);
			j++;
			cmd_mem_alloc(all);
			n = 0;
		}
		if (all->line[i - 1] == '|')
		{
			printf("pipe here\n");
			printf("j = %i\n", j);
			// extract_cmd_name(all, j);
			check_echo_n_flag(all, j);
			j++;
			cmd_mem_alloc(all);
			n = 0;
			all->p_num++;
		}
		free(tmp);
	}
	// extract_cmd_name(all, all->cmd_n - 2); //последняя команда не попадает под условие if (line[i - 1] == ';')
	if (!all->cmd[j].null && all->cmd[j].arg)
	{
		check_echo_n_flag(all, j);
		// buildin_func(all, arg, envp); заменила на semicolon_or_pipe
		semicolon_or_pipe(all, arg, envp);
	}
	print_parsed_string(all);
}



//echo                                \"   ckjvckvj     \"  kjfdvkdjf                           j
// echo \"\"    \"\"
// echo \" \"    \" \"
//("echo \"\" fff  \"   \"");
//("echo \"something\" \"  \"  ab\"\" .");
//echo \"  \"    \"  \"\"\"
//echo \"\'cd\'\"
//echo \'a  \"  \"  a\'
//echo \"a  \'  \'  a\"
//echo \'\'\'\"asd