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

void handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		rl_replace_line("", 0);
	}
}

void loop(void)
{
	char *input;
	char *user;

	signal(SIGINT, &handler);
	input = NULL;
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
	//parse_string("echo $TEST$TEST=lol$TEST\"\"lol");
}