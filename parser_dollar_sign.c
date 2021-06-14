/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dollar_sign.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 15:39:22 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/06/14 21:31:53 by kmeeseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static void	repl_env_name_with_value(char *line, int i, char *str, int name_len) //не работает с ненайденными переменными : echo $PWDklklk
{
	char	*tmp;
	char	*env_val;
	int		line_len;
	int		val_len;
	int 	t;

	line_len = ft_strlen(line);
	val_len = ft_strlen(str) - name_len;
	env_val = ft_substr(str, name_len, val_len);
	printf("env_val = |%s|\n\n", env_val);
	tmp = ft_calloc((line_len - name_len + val_len + 1), sizeof(char));
	printf("tmp_len = |%i|\n\n", (line_len - name_len + val_len + 1));

	line_len = ft_strlcpy(tmp, line, i + 1);
	printf("tmp_1_trird = |%s|\n", tmp);
	printf("line_len = |%i|\n\n", line_len);

	t = ft_strlcpy(&tmp[i], env_val, val_len + 1);
	printf("tmp_2_trird = |%s|\n", tmp);
	printf("line_len = |%i|\n", line_len);

	printf("i = %i\n", i);
	printf("i = %i\n", val_len);
	printf("i = %i\n", name_len);
	t = ft_strlcpy(&tmp[i + val_len], &line[i + name_len], (line_len - i - name_len + 1));
	printf("tmp_3_trird = |%s|\n", tmp);
	printf("line_len = |%i|\n", line_len);

	// echo     $USER hhh
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
	int		n;

	tmp = ft_strdup(&line[i]);
	k = 0;
	while(tmp[k] != ' ' && tmp[k] != '\0')
		k++;
	if (k == 1)
		return;			//ничего не меняется если подается просто $
	printf("k = %i\n", k);
	tmp2 = ft_substr(tmp, 1, k - 1); //HOME
	free(tmp);
	tmp = ft_strjoin(tmp2, "=");
	printf("tmp = |%s|\n", tmp);
	n = find_env_index_in_arr(all->tline.env_arr, tmp);
	printf("env = |%s|\n", all->tline.env_arr[n]);
	if (k == -1)
		repl_env_name_with_value(line, i, "", k);
	else
		repl_env_name_with_value(line, i, all->tline.env_arr[n], k);
	// return (0);
}