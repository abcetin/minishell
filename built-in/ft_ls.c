#include "../minishell.h"

void ls(t_cmd **cmd)
{
	(*cmd)->cmd = ft_strjoin("/bin/", (*cmd)->cmd);
	ft_execve(cmd);
}