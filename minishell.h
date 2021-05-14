#ifndef MINISHELL_H
# define MINISHELL_H
# define UP "\e[A"
# define DWN "\e[B"
# define OPT_UP "\e[1;3A"
# define OPT_DWN "\e[1;3B"
# define SHF_UP "\e[1;2A"
# define SHF_DWN "\e[1;2B"
# define CTRL_UP "\e[1;5A"
# define CTRL_DWN "\e[1;5B"

# include <stdio.h>
# include <unistd.h>
# include <string.h> 
# include "libft_ash/libft.h"
# include "get_next_line.h"
# include <curses.h>
# include <term.h>

// typedef struct s_flags
// {
//     char *flag;
// } t_flags;


typedef struct s_command
{
	char	*flag;
	char	*buildin_cmd;
	int		echo;
	int		cd;
	int		pwd;
	int		export;
	int		unset;
	int		env;
	int		exit;
}   t_command;

int		ft_strcmp(char *s1, char *s2);
int	ft_putchar(char c);
char	*read_line(int fd);

#endif