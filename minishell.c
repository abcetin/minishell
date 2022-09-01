#include "minishell.h"

char *rl_gets(char *str, const char *prompt)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
	str = readline(prompt);
	if (str && *str)
		add_history(str);
	return (str);
}

void loop(void)
{
	char *input;
	char *user;

	input = NULL;
	getenv("LOGNAME");
	user = ft_strjoin("\033[0;36m", getenv("LOGNAME"));
	user = ft_strjoin2(user, " %\e[0m ");
	while (1)
	{
		input = rl_gets(input, user);
		if (!input)
		{
			write(2, "exit\n", 6);
			exit(0);
		}
		parse_string(input);
	}
}

int main(void)
{

	loop();
	// parse_string("cat minishell.c | cat files4");
}