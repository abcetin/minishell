#include "minishell.h"

void    ls(char **cmd)
{
    int pid;
    char *arg[3];

    pid = fork();
    if (pid == 0)
    {
        arg[0] = "/usr/bin/ls";
        if (cmd[1] != NULL)
            arg[1] = cmd[1];
        else
            arg[1] = NULL;
        arg[2] =  NULL;
        execve(arg[0], arg, NULL);
    }
    else
        wait(NULL);
}