#include "minishell.h"

void loop(void)
{
	char *input;
	char *user;

	getenv("LOGNAME");
	user = ft_strjoin("\033[0;36m", getenv("LOGNAME"));
	user = ft_strjoin(user, " %\e[0m ");
	while (1)
	{
		input = readline(user);
		if (ft_strlen(input))
		{
			add_history(input);
			parse_string(input);
		}
	}
}

int main(void)
{

	// signal(SIGQUIT, handler);
	loop();
}