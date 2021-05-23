/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 16:04:37 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/05/23 19:22:19 by kmeeseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

// gcc parser_main.c parcer.c minishell.h libft/libft.a

void	realloc_cmd(t_all *all)
{
	
}

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

//  void 	first_mem_alloc(t_all *all)
//  {
// 	int i;

// 	i = 0;
// 	all->cmd_n = all->cmd_n + 7;
// 	// all->cmd[i].arg_n = 7;
// 	all->cmd = ft_calloc(all->cmd_n, sizeof(t_cmd));
// 	// if (!all->cmd)
// 	// 	error();
// 	// all->cmd[all->cmd_n] = 0;
// 	while (i < all->cmd_n)
// 	{
// 		all->cmd[i].arg_n = 7;
// 		all->cmd[i].arg = ft_calloc(all->cmd[i].arg_n, sizeof(char*));
// 		all->cmd[i].redir = ft_calloc(all->cmd[i].arg_n, sizeof(char*));
// 		i++;
// 	}
//  }

void 	cmd_mem_alloc(t_all *all, int i)
{
	all->cmd[i].arg_n = all->cmd[i].arg_n + 3;
	all->cmd[i].arg = ft_calloc(all->cmd[i].arg_n, sizeof(char *)); //не забудь проверку на NULL
	// all->cmd[i].redir = ft_calloc(all->cmd[i].arg_n, sizeof(char *)); //не забудь проверку на NULL
}

void 	cmd_arr_mem_alloc(t_all *all)
{
	int i;
	int old_cmd_n;
	t_cmd *tmp;

	i = 0;
	old_cmd_n = all->cmd_n;
	all->cmd_n = all->cmd_n + 4;
	if (!all->cmd)
	{
		all->cmd = ft_calloc(all->cmd_n, sizeof(t_cmd)); //не забудь проверку на NULL
		while (i < all->cmd_n)
		{
			all->cmd[i].arg_n = 0;
			cmd_mem_alloc (all, i);
			i++;
		}
	}
	else
	{
		tmp = ft_calloc(all->cmd_n, sizeof(t_cmd)); //не забудь проверку на NULL
		while (i < old_cmd_n)
		{
			// tmp->name = all->cmd->name;
			tmp->arg_n = all->cmd->arg_n;
			tmp->arg = all->cmd->arg;
			// tmp->redir = all->cmd->redir;
			// tmp->echo_n = all->cmd->echo_n;
			// tmp->doub = all->cmd->doub;
			// tmp->sing = all->cmd->sing;
			i++;
		}
		all->cmd = tmp;
		free(tmp);
		// i = 0;
		// while (old_cmd_n < all->cmd_n)
		// {
		// 	all->cmd[old_cmd_n].arg_n = 0;
		// 	cmd_mem_alloc (all, old_cmd_n);
		// 	old_cmd_n++;
		// }
	}
}

void	parser(char *line, t_all *all)
{
	int i;
	int j;
	int k;
	int n;
	int	line_len;
	char *tmp;

	i = 0;
	j = 0;
	n = 0;
	all->cmd_n = 0;
	line = ft_strtrim(line, " ");
	line_len = ft_strlen(line);
	// first_mem_alloc(all);
	cmd_arr_mem_alloc(all);
	while(line[i])
	{
		// if (j % 3 == 0)
		// 	cmd_arr_mem_alloc(all);
		k = 0;
		while (line[i] == ' ')
			i++;
		tmp = malloc(line_len);
		while (line[i] != ' ' && line[i])
		{
			if (line[i] == ';')
			{
				i++;
				// k++;
			}
			else
				tmp[k++] = line[i++];
		}
		tmp[k] = '\0';
		if (line[i - 1] == ';')
		{
			j++;
			n = 0;
		}
		else
		{
			all->cmd[j].arg[n] = malloc(ft_strlen(tmp));
			ft_strcpy(all->cmd[j].arg[n], tmp);
			n++;
			all->cmd->arg_n = n;
		}
		free(tmp);
		// int z = make_line(all->cmd[j].arg[n], line[i]);
		// all->cmd[j].arg[n][k] = line[i];
	}
		// if (all->cmd_n % 3 == 0)
		// 	cmd_arr_mem_alloc(all);
	n = 0;
	j = 0;
	while (all->cmd[j].arg[n])
	{
		while (all->cmd[j].arg[n])
		{
			printf("%p\n", all->cmd[j].arg[n]);
			printf("%i - %s\n", n, all->cmd[j].arg[n]);
			printf("%i - %i\n", n, all->cmd[j].arg_n);
			n++;
		}
		j++;
		n = 0;
		// printf("4 - %s\n", all->cmd[j].arg[4]);
		// printf("4 - %p\n", all->cmd[j].arg[4]);
		// printf("5 - %p\n", all->cmd[j].arg[5]);
		// printf("5 - %s\n", all->cmd[j].arg[5]);
		// printf("6 - %p\n", all->cmd[j].arg[6]);
		// printf("6 - %s\n", all->cmd[j].arg[6]);
		// printf("7 - %p\n", all->cmd[j].arg[7]);
		// printf("7 - %s\n", all->cmd[j].arg[7]);
		// printf("%s\n", all->cmd[j].arg[7]);
	}
}
// void insert_arg(char * arg);
