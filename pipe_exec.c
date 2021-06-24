#include  "minishell.h"                          //
                                                 //
void    pipe_exec(t_all *all, char**argv, char **envp)
{
    int fd[2];
    pid_t *pid;                                 //
                                                 //
    pipe(fd);                                    // [STDIN -> terminal_input, STDOUT -> terminal_output, fd[0] -> pipe_input, fd[1] -> pipe_output]
    pid = malloc(sizeof(pid_t) * all->p_num);
    while (all->p_num--)
    {
        pid[all->p_num] = fork();
        if (pid[all->p_num] == 0)                                  //
        {                                            // I am going to be the wc process (i.e. taking input from the pipe)
            close(fd[0]);                    // [STDIN -> terminal_input, STDOUT -> terminal_output, fd[1] -> pipe_output] (of the WC process)
            dup2(fd[1], STDIN_FILENO);      // [STDIN -> pipe_output, STDOUT -> terminal_output, fd[1] -> pipe_output]    (of the WC process)
            close(fd[1]);                   // [STDIN -> pipe_output, STDOUT -> terminal_output]                          (of the WC process)
            buildin_func(all, argv, envp);   //
        }                                            //
        else                                         //
        {                                            //
            pid[all->p_num] = fork();                             //                                      //
            if(pid[all->p_num]==0)                              //
            {                                        // I am going to be the ls process (i.e. producing output to the pipe)
                close(fd[0]);               // [STDIN -> terminal_input, STDOUT -> terminal_output, fd[0] -> pipe_input] (of the ls process)
                dup2(fd[1], STDOUT_FILENO);  // [STDIN -> terminal_input, STDOUT -> pipe_input, fd[0] -> pipe_input]      (of the ls process)
                close(fd[1]);                // [STDIN -> terminal_input, STDOUT -> pipe_input]                           (of the ls process)
                buildin_func(all, argv, envp); //
            }                                        //
                                                     //
            close(fd[1]);                   // [STDIN -> terminal_input, STDOUT -> terminal_output, fd[0] -> pipe_input] (of the parent process)
            close(fd[0]);                    // [STDIN -> terminal_input, STDOUT -> terminal_output]                      (of the parent process)
            waitpid(pid[all->p_num], NULL, 0);                    // As the parent process - we wait for a process to die (-1) means I don't care which one - it could be either ls or wc
            // waitpid(-1, NULL, 0);                    // As the parent process - we wait for the another process to die.
                                                     // At this point we can safely assume both process are completed
        }                                            //
    }
} 