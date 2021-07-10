#include  "../minishell.h"

void	free_int_arr(int **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	pipe_cycle(t_all *all, int i)
{
	pid_t	pid;

	if (i < all->p_num)
		pipe(all->fd[i]);
	pid = fork();
	if (pid == 0)
	{
		if (i < all->p_num)
			dup2(all->fd[i][1], 1);
		if (i != 0)
			dup2(all->fd[i - 1][0], 0);
		buildin_func(all);
		exit(0);
	}
	else
	{
		waitpid(pid, &g_status, 0);
		if (i != all->p_num)
			close(all->fd[i][1]);
		if (i != 0)
			close(all->fd[i - 1][0]);
	}
}

void	pipe_exec(t_all *all)
{
	int		k;
	int		i;

	k = all->p_num;
	i = 0;
	all->fd = ft_calloc((k + 1), sizeof(int *));
	while (i < k)
		all->fd[i++] = malloc(sizeof(int) * 2);
	i = 0;
	while (i < k + 1)
	{
		pipe_cycle(all, i);
		all->cmd_i++;
		i++;
	}
	free_int_arr(all->fd);
}
