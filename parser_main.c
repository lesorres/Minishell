/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 22:10:52 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/06/11 23:03:58 by kmeeseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	main()
{
	char *str;
	t_all all;

	str = ft_strdup("echo -n -n -n sjdhdsj lfllf flkgmblf"); //"'dfjkd'; dkjfd" //'dfjkd';ffg
	parser(str, &all);
	// free (str);
	// printf("%s", all.cmd.s_cmd[0].arg[1]);
	// printf("%s", all.cmd.s_cmd[0].arg[2]);
	// printf("%s", all.cmd.s_cmd[1].arg[1]);
	// printf("%s", all.cmd.s_cmd[1].arg[2]);
	return (0);
}