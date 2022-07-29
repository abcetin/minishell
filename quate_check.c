#include "minishell.h"

int first_quate(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == 34 || str[i] == 39))
			return (str[i]);
		i++;
	}
	return (0);
}

int first_index(char *str)
{
	int i;
	int j;

	i = 0;
	while (str[i])
	{
		if (str[i] != 32 && str[i - 1] == 32)
			j = i;
		if (str[i] == 34 || str[i] == 39)
			return (j);
		i++;
	}
	if (i == (int)ft_strlen(str))
		return (0);
	return (j);
}

int	last_index(char *str)
{
	int i;
	int ret;

	i = ft_strlen(str) - 1;
	ret = i;
	while (i >= 0)
	{
		if (str[i] != 32 && str[i + 1] == 32)
			ret = i;
		if (str[i] == 34 || str[i] == 39)
			return (ret);
		i--;
	}
	return (ret);
}

int quate_count(char *str)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			ret++;
		i++;
	}
	return (ret);
}

// static int is_exist(char *str, char c, int pos)
// {
// 	int i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == c && i != pos)
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

char *clear_quate(char *str)
{
	int i;
	int j;
	char *ret;
	int len;
	int quate_len;

	quate_len = quate_count(str);
	len = ft_strlen(str);
	ret = (char *)ft_calloc(sizeof(char), len - quate_len);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == first_quate(str) && ft_strchr(&str[i], first_quate(str)))
			continue;
		else
			ret[j++] = str[i];
	}
	return (ret);
}

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
	int		quate;

	i = -1;
	quate = first_quate(str);
	//str = clear_quate(str);
	while (str[++i])
	{
		if (str[i] == '$' && quate != 39)
			i += dolar_sign(&str[i]);
		if ((str[i] == first_quate(str) &&
			ft_strchr(&str[i], first_quate(str))))
			continue;
		else
			write(STDOUT_FILENO, &str[i], 1);
	}
}

// int main()
// {
// 	int fd = open("123.txt", O_RDONLY);
// 	char *str = ft_read(fd);
// 	//print_all(str);
// 	//printf("first %d last %d %zu\n", first_index(str), last_index(str), ft_strlen(str));
// 	//printf("%s\n", ft_cut_str(str, 8, 18));
// 	 char **a = split2(str);
// 	for (size_t i = 0; a[i]; i++)
// 	{
// 		printf("%s\n", a[i]);
// 	}
	
// 	// t_cmd *cmd;
// 	// cmd = malloc(sizeof(t_cmd));
// 	// arg(a, cmd);
// 	// option(a, cmd);
// 	// cmd->cmd = a[0];
// 	// ft_echo(&cmd);
	
// }