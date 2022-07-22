#include "minishell.h"

void exit_f(char **cmd)
{
    if (cmd[1])
    {
        write(STDOUT_FILENO, "too many arguments\n", 19);
        return ;
    }
    exit(EXIT_SUCCESS);
}

void pwd(char **cmd)
{
    char cwd[256];

    if (cmd[1] != NULL)
    {
        printf("pwd : too many arguments\n");
        return;
    }
    printf("%s\n", getcwd(cwd, sizeof(cwd)));
}

void cd(char **cmd)
{
    if (cmd[1] == NULL)
        chdir("/");
    if (chdir(cmd[1]) < 0)
        perror("");
}

void set_funcs(t_functions *func)
{
    func[0] = (t_functions){{(void *)pwd}, "pwd"};
    func[1] = (t_functions){{(void *)cd}, "cd"};
    func[2] = (t_functions){{(void *)exit_f}, "exit"};
    func[3] = (t_functions){{(void *)env}, "env"};
    func[4] = (t_functions){{(void *)export}, "export"};
    func[5] = (t_functions){{(void *)unset}, "unset"};
    func[6] = (t_functions){{(void *)ls}, "ls"};
    func[7] = (t_functions){{(void *)ft_cat}, "cat"};
    func[8] = (t_functions){{(void *)ft_grep}, "grep"};
    func[9] = (t_functions){{(void *)ft_wc}, "wc"};
    func[10] = (t_functions){{(void *)ft_echo}, "echo"};
    func[11] = (t_functions){{NULL}, NULL};
}

void *get_func(t_functions *function, char **cmd)
{
    int i;
    void *ret;

    ret = NULL;
    i = 0;
    while (function[i].arg != NULL)
    {
        if (ft_strstr(function[i].arg, cmd[0]))
        {
            ret = function[i].func.func_name(cmd);
            return (ret);
        }
        i++;
    }
    printf("command '%s' not found\n", cmd[0]);
    return (ret);
}

void with_pipe(char *str)
{
    int     count;
    char    **cmd;
    int     i;

    count = 0;
    i = 0;
    while (str[i])
    {
        if (str[i] == '|')
            count++;
        i++;
    }
    cmd = ft_split(str, '|');
    ft_pipe(cmd, count);
}

void    semicolon(char *str)
{
    char    **cmd;
    int     i;

    cmd = ft_split(str,  ';');
    i = 0;
    while (cmd[i])
	{
		parse_string(cmd[i]);
		i++;
	}  
}

void parse_string(char *str)
{
    char **cmd;
    t_functions *function;

    function = (t_functions *)malloc(sizeof(t_functions) * 12);
    set_funcs(function);
    // if (!str)
    //     return;
	if (ft_strchr(str, ';'))
		semicolon(str);
    else if (ft_strchr(str, '|') != 0)
        with_pipe(str);
    else
    {
        cmd = ft_split(str, 32);
        get_func(function, cmd);
    }
}
