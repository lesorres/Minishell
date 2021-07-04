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
# include <errno.h>
# include <sys/param.h>
# include <sys/types.h>
# include <sys/wait.h>


typedef struct s_lst
{
	char	*oldpwd;
	int		export_new_arg;
	int		get_env;
}	t_lst;

typedef struct	s_cmd
{
	// char	*name;
	int		arg_n;
	char	**arg;
	int		echo_n;
	int		null;
	int		dq_fl;
	int		sq_fl;
	int		i_rdir;
	int		o_rdir;
}				t_cmd;

typedef struct s_all
{
	int			cmd_n;
	t_cmd		*cmd;
	t_lst		builds;
	pid_t		*pid;
	t_termline	tline;
	int			status;
	char		**hist_arr; //возможно можно будет удалить 
	char		**path_arr;
	int			p_num; // количество пайпов
	// char		*tmp; //где используется?
	char		*line;
	int			cmd_i;
	int			in;
	int			out;
	int			set;			//зашла ли функция во второй цикл и нужно ли создавать аргумент по пустому tmp
	char		*tmp;
}				t_all;

int		status;

int		ft_putchar(char c);
char	*read_line(int fd);
int		len(char **str);
char	*add_quotes(t_all *all, char *line);
char	*add_path(t_all *all, char **envp);
void	add_oldpwd(t_all *all, char *path);
int		find_env_equal(char *line);
void	check_shlvl(t_all *all, char **envp);
void	int_sign(int sign);
void	quit_sign(int sign);
void	kill_sig(int sign);
int		check_valid_id(char *cmd, char *line);
int		find_equal_sign(t_all *all, char *line);
void	copy_env(t_all *all);
void	sort_env(t_all *all);
void	print_err2(char *cmd, char *err_name);
int		error_handler(char *arg1, char *arg2, char *err);

/*  buildin commands  */

void	buildin_func(t_all *all, char **arg, char **envp);
void	cmd_cd(t_all *all, char **envp, int k);
void	cmd_echo(t_all *all, char **argv, int k);
void	cmd_env(t_all *all, int k);
void	cmd_export(t_all *all, int k);

void	cmd_pwd(t_all *all, char **envp);
int		cmd_unset(t_all *all, int k);
void	cmd_exit(t_all *all, char **arg, int k);
int		cmp_path(t_all *all, char *str, char *name);
void	add_new_env_param(t_all *all, char *line);
void	get_envp(t_all *all, char **envp);
void	split_path(t_all *all);
void	pipe_exec(t_all *all, char**argv, char **envp);

/*  parser functions  */

// void	parser(t_all *all);
void	parser(t_all *all, char **arg, char **envp);
void	arr_mem_alloc(t_all *all, int j);
void	cmd_mem_alloc(t_all *all);
// int		compare_with_env(t_all *all, char *line, int i);
int		compare_with_env(t_all *all, char *line, int i);
int		process_redirections(t_all *all, int i, int j, int line_len);
int		skip_spaces(t_all *all, int i);

#endif