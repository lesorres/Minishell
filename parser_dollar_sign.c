/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dollar_sign.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 15:39:22 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/06/16 20:00:23 by kmeeseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static int	repl_env_name_with_value(t_all *all, int i, int env_i, int name_len) //не работает с ненайденными переменными : echo $PWDklklk
{
	char	*tmp;
	char	*env_val;
	int		line_len;
	int		val_len;
	int 	t;

	if (env_i == -1)
	{
		line_len = ft_strlen(all->line);
		tmp = ft_calloc((line_len - name_len + 1), sizeof(char));
		t = ft_strlcpy(tmp, all->line, i + 1);
		t = ft_strlcpy(&tmp[i], &all->line[i + name_len], (line_len - i - name_len + 1));
		// printf("tmp_3_trird = |%s|\n", tmp);

		free (all->line);
		all->line = tmp;
		return (0);
	}
	else
	{
		line_len = ft_strlen(all->line);
		val_len = ft_strlen(all->tline.env_arr[env_i]) - name_len;
		env_val = ft_substr(all->tline.env_arr[env_i], name_len, val_len);
		printf("\nenv_val = |%s|\n", env_val);
		tmp = ft_calloc((line_len - name_len + val_len + 1), sizeof(char));
		printf("tmp_len = |%i|\n", (line_len - name_len + val_len + 1));

		t = ft_strlcpy(tmp, all->line, i + 1);
		// printf("line_len = |%i|\n\n", line_len);
		printf("tmp_1_trird = |%s|\n", tmp);
		
		t = ft_strlcpy(&tmp[i], env_val, val_len + 1);
		printf("tmp_2_trird = |%s|\n", tmp);

		t = ft_strlcpy(&tmp[i + val_len], &all->line[i + name_len], (line_len - i - name_len + 1));
		printf("tmp_3_trird = |%s|\n", tmp);
		free (all->line);
		all->line = tmp;
		printf("line after f= |%s|\n", all->line);
		return (val_len);
	}
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

int	compare_with_env(t_all *all, char *line, int i)
{
	char	*tmp;
	char	*tmp2;
	int		k;		//длина имени переменной окружения с $
	int		n;		//индекс нужной переменной в массиве
	int val_len;

	tmp = ft_strdup(&line[i]);
	k = 0;
	while (tmp[k] != ' ' && tmp[k] != '\0')
		k++;
	if (k == 1)
		return (1);			//ничего не меняется если подается просто $
	tmp2 = ft_substr(tmp, 1, k - 1); //HOME
	free(tmp);
	tmp = ft_strjoin(tmp2, "="); //HOME=
	n = find_env_index_in_arr(all->tline.env_arr, tmp);
	val_len = repl_env_name_with_value(all, i, n, k);
	return (val_len);
}

//echo $echo $PWDfff  echo fgfgfgf $PWhdjhd dfhjdfh  echo   $rrrr jhj h h h  