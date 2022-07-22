#include "minishell.h"


int main(void)
{
	char	*input;
	char	*user;
	
	getenv("LOGNAME");
	user = ft_strjoin("\033[0;36m" ,getenv("LOGNAME"));
	user = ft_strjoin(user, " %\e[0m ");
	
	//signal(SIGQUIT, handler);
	while (1)
	{
		input = readline(user);
		rl_redisplay();
		if (ft_strlen(input))
		{
			add_history(input);
			parse_string(input);
		}
	}
}