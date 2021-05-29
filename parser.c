/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 16:04:37 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/05/28 20:28:21 by kmeeseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

// int add_char(char *arg, char c)
// {
// 	int len;
// 	int new_len;
// 	char *ret;
// 	len = ft_strlen(arg);
// 	new_len = len + 2;
// 	if (!(ret = malloc(sizeof(char) * (new_len))))
// 		return (0);
// 	ret[new_len - 2] = c;
// 	ret[new_len - 1] = '\0';
// 	while (len-- >=0)
// 		ret[len] = arg[len];
// 	free(arg);
// 	arg = ret;
// 	return (1);
// }

// int	make_line(char *arg, char c)
// {
// 	if (!(arg))
// 	{
// 		arg = malloc(sizeof(char));
// 		if (!(arg))
// 			return (0);
// 		arg[0] = '\0';
// 	}
// 	if (c =='\0')
// 		return (0);
// 	add_char(arg, c);
// 	return(1);
// }

// void 	arr_mem_alloc(t_all *all, int i, int n)
// {
// 	all->cmd[i].arg = ft_calloc(n, sizeof(char *)); //не забудь проверку на NULL
// 	// all->cmd[i].redir = ft_calloc(all->cmd[i].arg_n, sizeof(char *)); //не забудь проверку на NULL
// }

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
		// i = 0;
		// while (old_cmd_n < all->cmd_n)
		// {
		// 	all->cmd[old_cmd_n].arg_n = 0;
		// 	arr_mem_alloc (all, old_cmd_n);
		// 	old_cmd_n++;
		// }
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
		if (all->cmd)
			free(all->cmd);
		all->cmd = tmp;
		all->cmd[old_cmd_n].arg_n = 1;
		all->cmd[all->cmd_n - 1].null = 1;
		all->cmd[old_cmd_n].null = 0;
		// i = 0;
		// while (old_cmd_n < all->cmd_n)
		// {
		// 	all->cmd[old_cmd_n].arg_n = 0;
		// 	arr_mem_alloc (all, old_cmd_n);
		// 	old_cmd_n++;
		// }
	}
}

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
		while (line[i] == ' ')
			i++;
		tmp = malloc(line_len);
		while (line[i] != ' ' && line[i])
		{
			if (line[i] == ';')
			{
				i++;
			}
			else
				tmp[k++] = line[i++];
		}
		tmp[k] = '\0';
		if (line[i - 1] == ';')
		{
			j++;
			cmd_mem_alloc(all);
			n = 0;
		}
		else //здесь записываем слова в массив
		{
			arr_mem_alloc(all, j);
			all->cmd[j].arg[n] = malloc(ft_strlen(tmp));
			ft_strcpy(all->cmd[j].arg[n], tmp);
			n++;
			// all->cmd->arg_n = n;
		}
		free(tmp);
		// int z = make_line(all->cmd[j].arg[n], line[i]);
		// all->cmd[j].arg[n][k] = line[i];
	}
		// if (all->cmd_n % 3 == 0)
		// 	cmd_mem_alloc(all);
	n = 0;
	j = 0;
	while (!all->cmd[j].null && all->cmd[j].arg[n])
	{
		while (all->cmd[j].arg[n])
		{
			printf("adr = |%p|\n", all->cmd[j].arg[n]);
			printf("str(#%i %i) = %s\n", j, n, all->cmd[j].arg[n]);
			// printf("%i - %i\n", n, all->cmd[j].arg_n);
			n++;
		}
		j++;
		n = 0;
	}
	// printf("adr = |%p|\n", all->cmd[0].arg[0]);
	// printf("str(%i) = %s\n", 0, all->cmd[0].arg[0]);
	// printf("adr = |%p|\n", all->cmd[0].arg[1]);
	// printf("str(%i) = %s\n", 0, all->cmd[0].arg[1]);
	// printf("adr = |%p|\n", all->cmd[1].arg[0]);
	// printf("str(%i) = %s\n", 0, all->cmd[1].arg[0]);
}
