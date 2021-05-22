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


typedef struct s_command
{
	char	*flag;
	char	*buildin_cmd;
	int		echo;
	int		cd;
	int		pwd;
	int		exprt;
	int		unset;
	int		env;
	int		exit;
}   t_command;

typedef struct s_all
{
	char	**hist_arr;
    int     cmd_n;
    t_cmd   *cmd;
}				t_all;

int		ft_strcmp(char *s1, char *s2);
int		ft_putchar(char c);
char	*read_line(int fd);
void	parser(char *line, t_all *all);

/*  buildin commands  */

int 	cmd_echo(t_cmd *cmd, char **argv, char **envp);
int 	cmd_cd(t_cmd *cmd, char **argv, char **envp);
void    cmd_env(char **envp);
void    cmd_pwd(t_cmd *cmd, char **arg, char **envp);

#endif