#include "minishell.h"

void    ft_echo(char **cmd)
{
    if (cmd[1] && ft_strstr(cmd[1], "-n"))
    {
        if (cmd[2] && cmd[2][0] == '$')
            write(STDOUT_FILENO, getenv(&cmd[2][1]), ft_strlen(getenv(&cmd[2][1])));         
        else
            write(STDOUT_FILENO, cmd[2], ft_strlen(cmd[2]));
    }
    else if (cmd[1])
    {
        if (cmd[1] && cmd[1][0] == '$')
            write(STDOUT_FILENO, getenv(&cmd[1][1]), ft_strlen(getenv(&cmd[1][1]))); 
        else
            write(STDOUT_FILENO, cmd[1], ft_strlen(cmd[1]));
        write(STDOUT_FILENO, "\n", 1);  
    }
}