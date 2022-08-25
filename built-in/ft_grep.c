#include "../minishell.h"

void ft_grep(t_cmd **cmd)
{
	(*cmd)->cmd = ft_strjoin("/usr/bin/", (*cmd)->cmd);
	ft_execve(cmd);
}