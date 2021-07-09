#include "minishell.h"

# define UP "\e[A"
# define DWN "\e[B"
# define LEFT "\e[D"
# define RiGHT "\e[C"
# define TERM_NAME "xterm-256color"
# define PROMPT 12
# define PATH_LEN 1024
# define CMD_N_F "command not found"
# define EXP_NOT_VAL "not a valid identifier"

typedef struct s_termline
{
	int     cursor;
	int     symb_num;
	int     line_num;
	int		curr_line;
	int		env_line_num;
	char	*print_line;
	char    *hist_line;
	char    *str;
	char	**env_arr;
	int		exp_line_num;
	char	**export_arr;
	char	*replaced_str;
	char	*replaced_val;
	char	*val_str;
	int		equal_sign;
	int		first_shlvl;
	char    *path;
	char	*pwd;
	char	*new_name;
}   t_termline;

int	isdigit_line(char *str);