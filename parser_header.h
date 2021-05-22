/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_header.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 16:13:59 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/05/21 23:06:17 by kmeeseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HEADER_H
# define PARSER_HEADER_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>

typedef struct	s_cmd
{
	// int		av_arg_num;
	int		arg_n;
	char	*name;
	char	**arg;
	char	**redir;
	int		echo_n;
	int		doub;
	int		sing;
}				t_cmd;

#endif