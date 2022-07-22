#include "minishell.h"

static int where(char **s1, char *s2)
{
    int i;

    i = 0;
    while (s1[i] && ft_strnstr(s1[i], s2, ft_strlen(ft_split(s1[i], '=')[0])) == 0)
        i++;
    return (i);
}

void env(void)
{
    int i;

    i = 0;
    while (environ[i])
        printf("%s\n", environ[i++]);
}

void export(char **cmd)
{
    int count;
    int i;

    if (cmd[1] && ft_strchr(cmd[1], '=') == 0)
    {
        printf("'%s' not a valid identifier\n", cmd[1]);
        return;
    }
    i = 0;
    count = 0;
    while (environ[count])
        count++;
    i = where(environ, ft_split(cmd[1], '=')[0]);
    if (i == count)
    {
        environ = (char **)realloc(environ, ((count + 1) * sizeof(char *)));
        environ[count] = malloc(ft_strlen(cmd[1]));
        environ[count] = cmd[1];
        environ[count + 1] = NULL;
    }
    else
        environ[i] = cmd[1];
}

void unset(char **cmd)
{
    int i;
    int j;
    int count;

    i = 0;
    count = 0;
    j = 0;
    while (environ[count])
        count++;
    i = where(environ, cmd[1]);
    if (i == count)
        return;
    count = 0;
    while (environ[j])
    {
        if (i != j)
        {
            environ[count] = environ[j];
            count++;
        }
        j++;
    }
    environ = (char **)realloc(environ, ((count) * sizeof(char *)));
    environ[count] = NULL;
}