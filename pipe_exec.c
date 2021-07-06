#include  "minishell.h"

void free_int_2d_arr(int ***arr)
{
	int	i;
	
	i = 0;
	while ((*arr)[i])
		free((*arr)[i++]);
	free(*arr);
}

void	pipe_exec(t_all *all, char**argv, char **envp)
{
	int		**fd;
	pid_t	pid;
	char	c;
	int		status;
	int		k;
	int		i;

	k = all->p_num;
	i = 0;
	fd = (int**)malloc(sizeof(int*) * (k));
	while (i < (k + 1)){
		fd[i] = malloc(sizeof(int) * 2);
		i++;
	}
	i = 0;
	while (i < k + 1)
	{
		if (i < k)
			pipe(fd[i]);
		pid = fork();
		if (pid == 0)
		{
			if (i < k)
				dup2(fd[i][1], 1);
			if (i != 0)
				dup2(fd[i - 1][0], 0);
			buildin_func(all, argv, envp);
			// free_int_2d_arr(&fd);
			exit(0);
		}
		else
		{
			waitpid(pid, &status, 0);
			if (i != k)
				close(fd[i][1]);
			if (i != 0)
				close(fd[i - 1][0]);
		}
		all->cmd_i++;
		i++;
	}
	free_int_2d_arr(&fd);
}