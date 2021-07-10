#ifndef EXECUTE_HEADER_H
# define EXECUTE_HEADER_H

# include "minishell.h"
# define UP "\e[A"
# define DWN "\e[B"
# define K_LEFT "\e[D"
# define K_RIGHT "\e[C"
# define TERM_NAME "xterm-256color"
# define PROMPT 12
# define PATH_LEN 1024
# define CMD_N_F "command not found"
# define EXP_NOT_VAL "not a valid identifier"

typedef struct s_lst
{
	char	*oldpwd;
	int		export_new_arg;
	int		get_env;
	char	*str;
	int		fd;
	int		l;
}	t_lst;

typedef struct s_termline
{
	int		cursor;
	int		symb_num;
	int		line_num;
	int		curr_line;
	int		env_line_num;
	char	*print_line;
	char	*hist_line;
	char	**env_arr;
	int		exp_line_num;
	char	**export_arr;
	char	*replaced_str;
	char	*replaced_val;
	char	*val_str;
	int		equal_sign;
	int		first_shlvl;
	char	*path;
	char	*pwd;
	char	*new_name;
	int		unset_path;
}	t_termline;

int		isdigit_line(char *str);

#endif
