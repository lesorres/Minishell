#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include "libft/libft.h"
# include "execute_header.h"
# include <curses.h>
# include <term.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>
# include <sys/param.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_cmd
{
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
	t_lst		trm;
	pid_t		*pid;
	t_termline	tline;
	int			status;
	char		**path_arr;
	int			p_num;
	char		*line;
	int			cmd_i;
	int			**fd;
	char		*file_name;
	int			count;
	int			in;
	int			out;
	int			set;
	char		*tmp;
	int			line_len;
	char		**arg;
	char		**envp;
	int			redid_err;
}				t_all;

int		g_status;

int		ft_putchar(char c);
char	*read_line(int fd);
int		len(char **str);
void	__free_arr(char **arr);
char	*add_quotes(t_all *all, char *line);
char	*add_path(t_all *all);
void	add_oldpwd(t_all *all, char *path);
int		find_var_in_arr(char **arr, char *str);
int		find_env_equal(char *line);
void	check_shlvl(t_all *all);
void	int_sign(int sign);
void	quit_sign(int sign);
int		check_valid_id(char *cmd, char *line);
int		find_equal_sign(t_all *all, char *line);
void	copy_env(t_all *all);
void	sort_env(t_all *all);
void	print_err2(char *cmd, char *err_name);
int		check_path_exist(t_all *all);
int		error_handler(char *arg1, char *arg2, char *err);
void	free_cmd_lines(t_all *all);
void	free_path_arr(t_all *all);
void	check_if_path_arr_exists(t_all *all);
int		hist_line_num(int fd);
char	*get_hist_line(int num, int fd);
void	set_terminal(struct termios *term);
void	res_terminal(struct termios *term);
void	line_init(t_all *all, struct termios *term);
void	up_arrow(t_all *all);
void	down_arrow(t_all *all);
void	left_arrow(t_all *all);
void	right_arrow(t_all *all);
void	backspace_arrow(t_all *all);
void	exit_key(int fd);
void	write_line(t_all *all);
void	ctrl_c(t_all *all);

/*  buildin commands  */

void	buildin_func(t_all *all);
void	cmd_cd(t_all *all, int k);
void	cmd_echo(t_all *all, int k);
void	cmd_env(t_all *all, int k);
void	cmd_export(t_all *all, int k);
void	cmd_pwd(t_all *all);
int		cmd_unset(t_all *all, int k);
void	cmd_exit(t_all *all, int k);
int		cmp_path(t_all *all, char *str, char *name);
int		execute(t_all *all, char *name, char **arg);
void	add_new_env_param(t_all *all, char *line);
void	get_envp(t_all *all, char **envp);
void	split_path(t_all *all);
void	pipe_exec(t_all *all);

/*  parser functions  */

int		set_all_initial_params(t_all *all, int *i, int *j, int *n);
void	parser(t_all *all, char **arg, char **envp);
void	arr_mem_alloc(t_all *all, int j);
void	cmd_mem_alloc(t_all *all);
int		compare_with_env(t_all *all, char *line, int i);
void	process_dollar_sign(t_all *all, int *i, int *k);
int		process_redirections(t_all *all, int i, int j, int line_len);
int		skip_spaces(t_all *all, int i);
void	free_arr(char ***arr);
int		error(char *str, char c, char c2);
int		check_line_validity(char *line);
void	semicolon_or_pipe(t_all *all);
int		quotes_flags_switch(t_all *all, char *line, int i, int j);
int		process_quotes(t_all *all, int i, int *k, int j);
int		check_redir_err(t_all *all);
void	print_err3(t_all *all, char *cmd, char *err_name);

#endif