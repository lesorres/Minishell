#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include "libft/libft.h"
# include "get_next_line.h"
# include "execute_header.h"
# include <curses.h>
# include <term.h>
# include <fcntl.h>
# include <signal.h>
// # include "parser_header.h"
# include <errno.h>


typedef struct s_lst
{
	char	*oldpwd;
	int		export_new_arg;
	int		get_env;
}   t_lst;

typedef struct	s_cmd
{
	char	*name;
	int		arg_n;
	char	**arg;
	int		echo_n;
	int		null;
	int		dq_fl;
	int		sq_fl;
	char	**i_rdir;
	char	**o_rdir;
	// int		delim; //если 0 - точка с запятой, если 1 - пайп
}				t_cmd;

typedef struct s_all
{
    int     cmd_n;
    t_cmd   *cmd;
	t_lst	builds;
	t_termline tline;
	char	*status;
	char	**hist_arr; //возможно можно будет удалить 
	char	**path_arr;
	char	*tmp; //где используется?
	char	*line;
	int		p_num; // количество пайпов
}				t_all;

char	*status;

int		ft_putchar(char c);
char	*read_line(int fd);
int 	len(char **str);
char	*add_quotes(t_all *all, char *line);
char	*add_path(t_all *all, char **envp);
int		find_env_equal(char *line);
void	check_shlvl(t_all *all, char **envp);
void    int_sign(int sign);
void    quit_sign(int sign);
void    kill_sig(int sign);

/*  buildin commands  */

void	buildin_func(t_all *all, char **arg, char **envp);
void	cmd_cd(t_all *all, char **envp, int k);
void	cmd_echo(t_all *all, char **argv, int k);
void	cmd_env(t_all *all, int k);
void	cmd_export(t_all *all, int k);
void	cmd_pwd(t_all *all, char **envp);
int		cmd_unset(t_all *all, int k);
void	cmd_exit(t_all *all, char **arg, int k);
void	add_new_env_param(t_all *all, char *line);
void	get_envp(t_all *all, char **envp);
void	split_path(t_all *all);

/*  parser functions  */

// void	parser(t_all *all);
void	parser(t_all *all, char **arg, char **envp);
// int		compare_with_env(t_all *all, char *line, int i);
int		compare_with_env(t_all *all, char *line, int i);

#endif