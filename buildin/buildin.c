#include "../minishell.h"

void	replace_fd(t_all *all, int i)
{
	int	dp1;
	int	dp2;

	if (all->cmd[i].i_rdir == -1 || all->cmd[i].o_rdir == -1)
		return ;
	if (all->cmd[i].i_rdir != 0)
	{
		dp1 = dup2(all->cmd[i].i_rdir, 0);
		close(all->cmd[i].i_rdir);
	}
	if (all->cmd[i].o_rdir != 1)
	{
		dp2 = dup2(all->cmd[i].o_rdir, 1);
		close(all->cmd[i].o_rdir);
	}
}

void	close_fds(t_all *all, int i)
{
	if (all->cmd[i].i_rdir != 0)
	{
		close(all->cmd[i].i_rdir);
		dup2(all->in, 0);
	}
	if (all->cmd[i].o_rdir != 1)
	{
		close(all->cmd[i].o_rdir);
		dup2(all->out, 1);
	}
}

void	executer(t_all *all, char **arg, char **envp, int i)
{
	status = execute(all, all->cmd[i].arg[0], all->cmd[i].arg, envp);
	if (status >= 256)
		status /= 256;
	else if (status == 2 || status == 3)
		status += 128;
	if (all->status != 0)
	{
		status = all->status;
		all->status = 0;
	}
}

void	buildin_func(t_all *all, char **arg, char **envp)
{
	int	i;

	i = all->cmd_i;
	all->cmd_i++;
	replace_fd(all, i);
	if (!ft_strcmp(all->cmd[i].arg[0], "cd"))
		cmd_cd(all, all->tline.env_arr, i);
	else if (!ft_strcmp(all->cmd[i].arg[0], "echo"))
		cmd_echo(all, arg, i);
	else if (!ft_strcmp(all->cmd[i].arg[0], "pwd"))
		cmd_pwd(all, envp);
	else if (!ft_strcmp(all->cmd[i].arg[0], "export"))
		cmd_export(all, i);
	else if (!ft_strcmp(all->cmd[i].arg[0], "unset"))
		cmd_unset(all, i);
	else if (!ft_strcmp(all->cmd[i].arg[0], "env"))
		cmd_env(all, i);
	else if (!ft_strcmp(all->cmd[i].arg[0], "exit"))
		cmd_exit(all, arg, i);
	else
		executer(all, all->cmd[i].arg, envp, i);
	close_fds(all, i);
}
