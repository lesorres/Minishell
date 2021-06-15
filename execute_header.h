#include "minishell.h"

# define UP "\e[A"
# define DWN "\e[B"
# define LEFT "\e[D"
# define RiGHT "\e[C"
# define OPT_UP "\e[1;3A"
# define OPT_DWN "\e[1;3B"
# define SHF_UP "\e[1;2A"
# define SHF_DWN "\e[1;2B"
# define CTRL_UP "\e[1;5A"
# define CTRL_DWN "\e[1;5B"
# define TERM_NAME "xterm-256color"
# define PROMPT 12
# define PATH_LEN 1024

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