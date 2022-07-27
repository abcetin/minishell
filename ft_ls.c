#include "minishell.h"

void    ls(t_cmd **cmd)
{
    int pid;
    char *arg[3];

    pid = fork();
    if (pid == 0)
    {
        arg[0] = "/bin/ls";
        if ((*cmd)->option[0] != NULL)
            arg[1] = (*cmd)->option[0];
        else
            arg[1] = NULL;
        arg[2] =  NULL;
        execve(arg[0], arg, NULL);
    }
    else
        wait(NULL);
}