#include "../minishell.h"

int	dolar_sign(char *str)
{
	char *temp;
	int i;

	i = 0;
	temp = NULL;
	while (str[i])
	{
		if (str[i] != '$' && str[i] != '_' && !ft_isalpha(str[i]))
			break;
		i++;
	}
	temp = ft_substr(str, 0, i);
	//printf("%s\n", str);
	if (getenv(&temp[1]) == NULL)
			return (i);
	write(STDOUT_FILENO, getenv(&temp[1]), ft_strlen(getenv(&temp[1])));
	free(temp);
	return(i);
}

void print_all(char *str)
{
	int		i;
	int		quote;

	i = -1;
	quote = first_quote(str);
	printf("%s\n",str);
	//str = clear_quote(str);
	while (str[++i])
	{
		if (str[i] == '$' && quote != 39)
			i += dolar_sign(&str[i]);
		else if ((str[i] == quote && ft_strchr(&str[i], quote)))
			continue;
		write(STDOUT_FILENO, &str[i], 1);
	}
}