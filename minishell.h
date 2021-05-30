#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <string.h> 
# include "libft/libft.h"
# include "get_next_line.h"
# include "execute_header.h"
# include <curses.h>
# include <term.h>
# include <fcntl.h>
# include "parser_header.h"
# include <errno.h>


typedef struct s_lst
{
	char	*oldpwd;
	int		export_new_arg;
}   t_lst;

typedef struct s_all
{
	char	**hist_arr;
    int     cmd_n;
    t_cmd   *cmd;
	t_lst	builds;
	t_termline tline;
}				t_all;

int		ft_strcmp(char *s1, char *s2);
int		ft_putchar(char c);
char	*read_line(int fd);
void	parser(char *line, t_all *all);

/*  buildin commands  */

void	cmd_echo(t_all *all, char **argv);
int		cmd_cd(t_all *all, char **envp);
void    cmd_env(t_all *all);
void    cmd_export(t_all *all, char **envp);
void	cmd_pwd(t_all *all, char **envp);
void    buildin_func(t_all *all, char **arg, char **envp);

#endif