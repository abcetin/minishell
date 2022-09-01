#include "minishell.h"

// char    *rl_gets(char *str, const char *prompt)
// {
//     if (str)
//     {
//         free(str);
//         str = NULL;
//     }
//     str = readline(prompt);
//     if (str && *str)
//         add_history(str);
//     return (str);
// }

// void loop(void)
// {
//     char *input;
//     char *user;
//     char    *tmp;
//     getenv("LOGNAME");
//     user = ft_strjoin("\033[0;36m", getenv("LOGNAME"));
//     tmp = user;
//     user = ft_strjoin(user, " %\e[0m ");
//     free(tmp);
//     input = NULL;
//     while (1)
//     {
//         input = rl_gets(input, user);
//         if (!input || !ft_strncmp(input, "exit", ft_strlen("exit")))
//         {
//             write(2, "\nexit\n", 6);
//             exit(0);
//         }
//         parse_string(input);
//     }
// }

void loop(void)
{
	char *input;
	char *user;

	getenv("LOGNAME");
	user = ft_strjoin("\033[0;36m", getenv("LOGNAME"));
	user = ft_strjoin2(user, " %\e[0m ");
	while (1)
	{
		input = readline(user);
		if (ft_strlen(input))
		{
			add_history(input);
			parse_string(input);
		}
		free(input);
	}
}

int main(void)
{

	loop();
	//parse_string("cat minishell.c | cat files4");
}