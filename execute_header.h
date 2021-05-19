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

typedef struct s_termline
{
    int     cursor;
    int     num_symb;
}   t_termline;