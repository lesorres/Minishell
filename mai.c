#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void		print_arr(char **args)
{
	int i;

	i = 0;
	while (args[i])
	{
		printf("%s\n", args[i]);
		i++;
	}
	if (args[i] == NULL)
		printf("<null>\n");
}

int main(int argc, char **argv, char **envp)
{
		int **p;
		char buf[80];
		pid_t pid;
		char **arr;
		char **arr2;
		char **arr3;
		int exec;
		int  status;
	
		p = (int**)malloc(sizeof(int*) * 6);
		for (int i = 0; i < 6; i++)
			p[i] = (int*)malloc(sizeof(int) * 2);
		




		// int fd = open("bla.txt", O_WRONLY | O_CREAT | O_APPEND, 0777);
		// pipe(p)
		arr = malloc(sizeof(char *) * 4);
		arr2 = malloc(sizeof(char *) * 2);
		arr[0] = strdup("/usr/bin/grep");
		arr[1] = strdup("m");
		arr[2] = 0;
		// arr[2] = strdup("main.c");
		arr[3] = NULL;
		arr2[0] = strdup("/bin/ls");
		arr2[1] = NULL;
		arr3 = malloc(sizeof(char *) * 4);
		arr3[0] = strdup("/bin/cat");
		arr3[1] = strdup("-e");
		arr3[2] = 0;
		arr3[3] = NULL;
		int i = 0;
		while (i < 5){
			if (i < 4)	
				pipe(p[i]);

			pid = fork();

			if (pid == 0)
			{
				if(i < 4)	
					dup2(p[i][1], 1);
				if (i != 0)
					dup2(p[i - 1][0], 0);
				if (i == 0)
					execve(arr2[0], arr2, envp);
				else
					execve(arr3[0], arr3, envp);

				printf("error!\n");
				exit(0);
			}
			else
			{
				waitpid(pid, &status, 0);
				if (i != 4)
					close(p[i][1]);
				if (i != 0)
					close(p[i - 1][0]);
				printf("uraaa!\n");
			}
		i++;
		}

































		// pid = fork();
		// if (!pid)
		// {
		// 	close(0);
		// 	dup2(p[1], 1);
		// 	close(p[1]);
		// 	exec = execve(arr2[0], arr2, envp);
		// }
		// else
		// {
		// 	// pipe(p2);
		// 	pid = fork();
		// 	if (!pid)
		// 	{
		// 		dup2(p[0], 0);
		// 		close(p[1]);
		// 		close(p[0]);
		// 		execve(arr3[0], arr3, envp);
		// 	}
		// 	else
		// 	{
		// 		// wait(&pid);
		// 		// dup2(p2[1], 1);
		// 		close(p[1]);
		// 		// dup2(p2[1], 1);
		// 		close(p[0]);
		// 		// pid[2] = fork();
		// 		// if (!pid[2])
		// 		// {
		// 			// execve(arr[0], arr, envp);
		// 		waitpid(pid, &status, 0);
		// 	// read(0, buf, 80);
		// 	}
		
		// 	// 	write(1, buf, 80);
		// 	// char* cmds[] = { "/usr/bin/grep", "m", 0 };
		// 	// arr[2] = "0";
		// 	// arr[1]  = "m";
		// 	// if (!fork())
		// 	// {

		// 	// }
		// 	// while (1) ;
			
		// }
		// printf("exec = %d\n", exec);
		// if (exec == -1)
		// 	printf("error: exec = %d!\n", exec);
		// else
		// 	printf("ok\n");
			// close(1);
		// else
		// close(0);
		// if (pipe(p))
		// {
		//     perror("ошибка канала");
		//     exit(1);
		// }
		// if ((pid=fork()) == 0)
		// {
		//                            /* дочерний процесс */
		//     close(p[0]);           /*закрывает ненужный*/
		//                           /*дескриптор чтения*/
		//     sprintf(buf,"%d",getpid()); 
		//                            /* создание данных */
		//                            /*для отправки*/
		//     write(p[1],buf,strlen(buf)+1);
		//             /*запись данных с учетом байта null*/
		//     exit(0);
		// }
		//                                 /*родительский процесс*/
		// close(p[1]);                    /*закрыть ненужную сторону канала */
		// read(p[0],buf,sizeof(buf));     /*чтение данных из канала*/
		// printf("Сообщение дочернего процесса: %s/n", buf);
		//                                /*вывод результата*/
		// exit(0);
		return 0;
}