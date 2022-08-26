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

	i = 0;
	quote = first_quote(str);
	str = clear_quote(str);
	while (str[i] != '\0')
	{
		if (str[i] == '$' && quote != 39)
			i +=  dolar_sign(&str[i]);
		else
			write(STDOUT_FILENO, &str[i], 1);
		i++;
	}
}