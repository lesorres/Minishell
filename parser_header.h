/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_header.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 16:13:59 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/06/07 19:24:08 by kmeeseek         ###   ########.fr       */
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
	char	*name;
	int		arg_n;
	char	**arg;
	int		echo_n;
	int		null;
	int		dq_fl;
	int		sq_fl;
	char	**i_rdir;
	char	**o_rdir;
}				t_cmd;

#endif