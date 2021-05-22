/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 16:04:37 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/05/22 13:46:17 by kmeeseek         ###   ########.fr       */
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

 void 	first_mem_alloc(t_all *all)
 {
	int i;

	i = 0;
	all->cmd_n = 7;
	all->cmd = malloc(sizeof(t_cmd) * all->cmd_n);
	ft_bzero(all->cmd, all->cmd_n);
	// printf("%p", all->cmd);
	// if (!all->cmd)
	// 	error();
	// all->cmd[all->cmd_n] = 0;
	while (i < all->cmd_n)
	{
		all->cmd[i].arg = ft_calloc(all->cmd_n, sizeof(char*));
		// printf("%i - %p\n", i, all->cmd[i].arg[0]);
		// printf("%i - %p\n", i, all->cmd[i].arg[1]);
		// printf("%i - %p\n", i, all->cmd[i].arg[2]);
		// printf("%i - %p\n", i, all->cmd[i].arg[3]);
		// ft_bzero(all->cmd[i].arg, all->cmd_n);
		// all->cmd[i].arg[all->cmd_n - 1] = NULL;
		// printf("%i - %p\n", i, all->cmd[i].arg[0]);
		// printf("%i - %p\n", i, all->cmd[i].arg[1]);
		// printf("%i - %p\n", i, all->cmd[i].arg[2]);
		// printf("%i - %p\n", i, all->cmd[i].arg[3]);
		all->cmd[i].redir = ft_calloc(all->cmd_n, sizeof(char*)); //malloc(sizeof(char*) * all->cmd_n);
		// ft_bzero(all->cmd[i].redir, all->cmd_n);
		// all->cmd[i].redir[all->cmd_n - 1] = NULL;
		i++;
	}
		// printf("4 - %p\n", all->cmd[0].arg[4]);
		// printf("4 - %s\n", all->cmd[0].arg[4]);
		// printf("5 - %p\n", all->cmd[0].arg[5]);
		// printf("5 - %s\n", all->cmd[0].arg[5]);
		// printf("6 - %p\n", all->cmd[0].arg[6]);
		// printf("6 - %s\n", all->cmd[0].arg[6]);
		// printf("7 - %p\n", all->cmd[0].arg[7]);
		// printf("7 - %s\n", all->cmd[0].arg[7]);
 }

// void new_cmd()

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

	line = ft_strtrim(line, " ");
	line_len = ft_strlen(line);
	// count_max_words(line);
	first_mem_alloc(all);
 	while(line[i])
	{
		k = 0;
		/*if (line[i] == ' ')
		{
			n++;
			k = 0;
		}
		if (line[i] == ';')
		{
			j++;
			n = 0;
			k = 0;
		}
		k++;*/
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
		int l = ft_strlen(tmp);
		all->cmd[j].arg[n] = malloc(ft_strlen(tmp));
		ft_strcpy(all->cmd[j].arg[n], tmp);
		free(tmp);
		n++;
		all->cmd->arg_n = n;
		if (line[i - 1] == ';')
		{
			j++;
			n = 0;
		}
		// int z = make_line(all->cmd[j].arg[n], line[i]);
		// all->cmd[j].arg[n][k] = line[i];
	}
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
		// while (all->cmd[0].arg[n])
		// {
		// 	printf("%p\n", all->cmd[0].arg[n]);
		// 	printf("%s\n", all->cmd[0].arg[n++]);
		// }
		// while (all->cmd[1].arg[n])
		// {
			// printf("%p\n", all->cmd[1].arg[3]);
			// printf("%s\n", all->cmd[1].arg[n++]);
		// }
		// printf("4 - %p\n", all->cmd[j].arg[4]);
		// printf("4 - %s\n", all->cmd[j].arg[4]);
		// printf("5 - %p\n", all->cmd[j].arg[5]);
		// printf("5 - %s\n", all->cmd[j].arg[5]);
		// printf("6 - %p\n", all->cmd[j].arg[6]);
		// printf("6 - %s\n", all->cmd[j].arg[6]);
		// printf("7 - %p\n", all->cmd[j].arg[7]);
		// printf("7 - %s\n", all->cmd[j].arg[7]);
		// printf("%s\n", all->cmd[j].arg[7]);
		j++;
		n = 0;
	}
}
// void insert_arg(char * arg);
