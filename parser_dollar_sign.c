/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dollar_sign.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 15:39:22 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/06/14 17:33:33 by kmeeseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static void	repl_env_name_with_value(char *line, char *str, int i, int name_len)
{
	char	*tmp;
	int		line_len;

	line_len = ft_strlen(line);




}

static int	find_env_index_in_arr(char **arr, char *str)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		if (ft_strncmp(arr[i], str, ft_strlen(str)) == 0)
			break;
		i++;
	}
	if (arr[i] == NULL)
		i = -1;			// если переменную не нашли нужную переменную окружения
	return(i);
}

void	compare_with_env(t_all *all, char *line, int i)
{
	char	*tmp;
	char	*tmp2;
	int		k;
	int		name_len;

	tmp = ft_strdup(&line[i]);
	k = 0;
	while(tmp[k] != ' ' && tmp[k] != '\0')
		k++;
	printf("k = %i\n", k);
	tmp2 = ft_substr(tmp, 1, k - 1); //HOME
	free(tmp);
	tmp = ft_strjoin(tmp2, "=");
	printf("str = |%s|\n", tmp);
	k = find_env_index_in_arr(all->tline.env_arr, tmp);
	printf("env = |%s|\n", all->tline.env_arr[k]);
	// name_len = ft_strlen()
	// if (k = -1)
	// 	repl_env_name_with_value(line, "", i,  name_len);
	// else
	// 	repl_env_name_with_value(line, all->tline.env_arr[k], i, name_len);
	
	// return (0);
}