#include  "minishell.h"                          //
                                                 //
void    pipe_exec(t_all *all, char**argv, char **envp)
{
    int     fd[2];
    pid_t   *pid;
    int     status;
    int     k;                                 //
                                                 //
    pipe(fd);
    k = all->p_num;                                    // [STDIN -> terminal_input, STDOUT -> terminal_output, fd[0] -> pipe_input, fd[1] -> pipe_output]
    pid = malloc(sizeof(pid_t) * k);
    while (k > 0)
    {
        printf("k = %d\n", k);
        pid[k] = fork();
        if (pid[k] == 0)                                  //
        {                                            // I am going to be the wc process (i.e. taking input from the pipe)
            close(fd[0]);                    // [STDIN -> terminal_input, STDOUT -> terminal_output, fd[1] -> pipe_output] (of the WC process)
            printf("child with pid = %d\n", pid[k]);
            dup2(fd[1], STDOUT_FILENO);      // [STDIN -> pipe_output, STDOUT -> terminal_output, fd[1] -> pipe_output]    (of the WC process)
            close(fd[1]);                   // [STDIN -> pipe_output, STDOUT -> terminal_output]                          (of the WC process)
            printf("close fd[1]\n");
            printf("close fd[0]\n");
            buildin_func(all, argv, envp);
            all->cmd_i++;   //
        }                                            //
        else                                         //
        {                                            //
            wait(&pid[k]);
            // pid[k] = fork();
            // printf("parent with pid = %d\n", pid[k]);                             //                                      //
            // if(pid[k] == 0)                              //
            {                                        // I am going to be the ls process (i.e. producing output to the pipe)
                dup2(fd[0], STDIN_FILENO);  // [STDIN -> terminal_input, STDOUT -> pipe_input, fd[0] -> pipe_input]      (of the ls process)
                close(fd[0]);                // [STDIN -> terminal_input, STDOUT -> pipe_input]                           (of the ls process)
                close(fd[1]);               // [STDIN -> terminal_input, STDOUT -> terminal_output, fd[0] -> pipe_input] (of the ls process)
            buildin_func(all, argv, envp);
            all->cmd_i++; 
            }
            // wait(&pid[k]);
            close(fd[1]);                   // [STDIN -> terminal_input, STDOUT -> terminal_output, fd[0] -> pipe_input] (of the parent process)
            close(fd[0]);                    // [STDIN -> terminal_input, STDOUT -> terminal_output]                      (of the parent process)
            // waitpid(pid[k], &status, 0);                    // As the parent process - we wait for a process to die (-1) means I don't care which one - it could be either ls or wc
            // waitpid(-1, NULL, 0);                    // As the parent process - we wait for the another process to die.
                                                     // At this point we can safely assume both process are completed
        }
        k--;
    }
} 