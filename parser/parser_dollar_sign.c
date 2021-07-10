/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dollar_sign.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhyman <fhyman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 15:39:22 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/07/10 22:29:57 by fhyman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	in_case_env_var_was_found(t_all *all, int i, int env_i, int name_len)
{
	char	*tmp;
	char	*env_val;
	int		line_len;
	int		val_len;
	int		t;

	line_len = ft_strlen(all->line);
	val_len = ft_strlen(all->tline.env_arr[env_i]) - name_len;
	env_val = ft_substr(all->tline.env_arr[env_i], name_len, val_len);
	tmp = ft_calloc((line_len - name_len + val_len + 1), sizeof(char));
	t = ft_strlcpy(tmp, all->line, i + 1);
	t = ft_strlcpy(&tmp[i], env_val, val_len + 1);
	t = ft_strlcpy(&tmp[i + val_len], &all->line[i + name_len],
			(line_len - i - name_len + 1));
	free (all->line);
	free (env_val);
	all->line = tmp;
	return (val_len);
}

static int	repl_env_name_with_value(t_all *all, int i, int env_i, int name_len)
{
	char	*tmp;
	int		line_len;
	int		t;

	if (env_i == -1)
	{
		line_len = ft_strlen(all->line);
		tmp = ft_calloc((line_len - name_len + 1), sizeof(char));
		t = ft_strlcpy(tmp, all->line, i + 1);
		t = ft_strlcpy(&tmp[i], &all->line[i + name_len],
				(line_len - i - name_len + 1));
		free (all->line);
		all->line = tmp;
		if (!all->tmp[0])
			all->set = 0;
		return (0);
	}
	else
		return (in_case_env_var_was_found(all, i, env_i, name_len));
}

static int	find_env_index_in_arr(char **arr, char *str)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		if (ft_strncmp(arr[i], str, ft_strlen(str)) == 0)
			break ;
		i++;
	}
	if (arr[i] == NULL)
		i = -1;
	return (i);
}

int	compare_with_env(t_all *all, char *line, int i)
{
	char	*tmp;
	char	*tmp2;
	int		val_len;
	int		k;
	int		n;

	k = 1;
	tmp = ft_strdup(&line[i]);
	while ((tmp[k] > 64 && tmp[k] < 91) || (tmp[k] > 96 && tmp[k] < 123)
		|| (tmp[k] > 47 && tmp[k] < 58) || tmp[k] == '_')
		k++;
	if (k == 1)
	{
		free(tmp);
		return (1);
	}
	tmp2 = ft_substr(tmp, 1, k - 1);
	free(tmp);
	tmp = ft_strjoin(tmp2, "=");
	n = find_env_index_in_arr(all->tline.env_arr, tmp);
	val_len = repl_env_name_with_value(all, i, n, k);
	free (tmp);
	free (tmp2);
	all->tmp = ft_realloc(all->tmp, ft_strlen(all->line));
	return (val_len);
}

void	process_dollar_sign(t_all *all, int *i, int *k)
{
	int		z;
	int		val_len;
	char	*loc_stat;

	loc_stat = ft_itoa(g_status);
	if (all->line[*i] == '$' && all->line[*i + 1] == '?')
	{
		*i = *i + 2;
		z = 0;
		while (loc_stat[z])
			all->tmp[(*k)++] = loc_stat[z++];
	}
	else if (all->line[*i] == '$' && 47 < all->line[*i + 1]
		&& all->line[*i + 1] < 58)
		*i = *i + 2;
	else if (all->line[*i] == '$')
	{
		val_len = compare_with_env(all, all->line, *i);
		while (all->line[*i] && val_len > 0)
		{
			all->tmp[(*k)++] = all->line[(*i)++];
			val_len--;
		}
	}
	free(loc_stat);
}
