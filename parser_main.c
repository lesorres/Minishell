/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 22:10:52 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/06/16 20:06:21 by kmeeseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	main()
{
	// char *str;
	t_all all;

	all.line = ft_strdup("echo $echo $PWDfff  echo fgfgfgf $PWhdjhd dfhjdfh  echo   $rrrr jhj h h h");
	all.tline.env_arr = ft_calloc(6, sizeof(char*));
	all.tline.env_arr[0] = "PWD=/Users/kmeeseek/Desktop/minishell";
	all.tline.env_arr[1] = "PATH=/Users/kmeeseek/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/share/dotnet:/usr/local/munki:~/.dotnet/tools:/Users/kmeeseek/.brew/bin";
	all.tline.env_arr[2] = "HOME=/Users/kmeeseek";
	all.tline.env_arr[3] = "USER=kmeeseek";
	all.tline.env_arr[4] = "VSCODE_GIT_ASKPASS_NODE=/Applications/Visual Studio Code.app/Contents/Frameworks/Code Helper (Renderer).app/Contents/MacOS/Code Helper (Renderer)";
	
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