/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_header.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 16:13:59 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/05/16 21:02:22 by kmeeseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HEADER_H
# define PARSER_HEADER_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>

typedef struct	s_s_cmd
{
	// int		av_arg_num;
	int		arg_num;
	char	**arg;
	char	**redir;
	int		echo_n;
}				t_s_cmd;

typedef struct	s_cmd
{
	// int		av_s_cmd_num;
	int		cmd_num;
	t_s_cmd	**s_cmd; //	s_cmd	**s_cmd_arr;
	// char	*out_fl;
	// char	*inpt_fl;
	// char	*err_fl;
	// int		background; //нужен ли?
	//что за функции в структуре? - стр 5 - https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
}				t_cmd;

#endif