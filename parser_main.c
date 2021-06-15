/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 22:10:52 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/06/15 17:44:15 by kmeeseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	main()
{
	// char *str;
	t_all all;

	all.line = ft_strdup("echo blabla blabla $kjdfkjdjkj $PWD $HOME $NAME $jhdjhfbb $USER");
	all.tline.env_arr = ft_calloc(4, sizeof(char*));
	all.tline.env_arr[0] = "PWD=pwd";
	all.tline.env_arr[1] = "HOME=home";
	all.tline.env_arr[2] = "USER=user";
	
	//"'dfjkd'; dkjfd" //'dfjkd';ffg
	//"echo sjdhdsj lfllf flkgmblf ; echo -n; echo ----n; echo -n-n-n jjj; echo -nnn- ; echo -nnn -nnn j; echo n n; echo -nf"

	parser(&all);

	// free (str);
	// printf("%s", all.cmd.s_cmd[0].arg[1]);
	// printf("%s", all.cmd.s_cmd[0].arg[2]);
	// printf("%s", all.cmd.s_cmd[1].arg[1]);
	// printf("%s", all.cmd.s_cmd[1].arg[2]);
	return (0);
}