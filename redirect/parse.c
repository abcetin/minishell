// #include <string.h>
// #include "../minishell.h"

// int	quote_state(char *str, int pos)
// {
// 	int ret;
// 	int i;

// 	ret = 0;
// 	i = 0;
// 	while (str[i] && i < pos)
// 	{
// 		if ((str[i] == 34 || str[i] == 39) && ret == 0)
// 			ret = 1;
// 		else if ((str[i] == 34 || str[i] == 39) && ret == 1)
// 			ret = 0;
// 		i++;
// 	}
// 	return(ret);
// }

// int char_coun(char *str, char c)
// {
// 	int i;
// 	int ret;

// 	i = 0;
// 	ret = 0;
// 	while (str[i])
// 	{
// 		if (str[i + 1] != c && str[i] == c && !quote_state(str, i))
// 		 	ret++;
// 		i++;
// 	}
// 	return (ret + 1);
// }

// int amk(char *dst, char **src, char c)
// {
// 	int i;

// 	i = 0;
// 	while (dst[i])
// 	{
// 		if (dst[i] == c && !quote_state(dst, i))
// 			break;
// 		i++;
// 	}
// 	*src = ft_substr(dst, 0, i);
// 	return (i);
// }

// char **parsing_command(char *str, char c)
// {
// 	int i;
// 	int len;
// 	char **ret;
// 	int ret_index;

// 	len = -1;
// 	ret_index = -1;
// 	i = 0;
// 	ret = malloc(sizeof(char *) * (char_coun(str, c) + 1));
// 	while (++len < char_coun(str, c))
// 	{
// 		while (str[i] == c)
// 			i++;
// 		if (str[i] == 34 || str[i] == 39)
// 			i += amk(&str[i], &ret[++ret_index], c);
// 		else if (str[i] != c && str[i] != 34 && str[i] != 39)
// 			i += amk(&str[i], &ret[++ret_index], c);
// 	}
// 	ret[++ret_index] = NULL;
// 	return (ret);
// }

// int main()
// {
// 	char *i;
// 	int a = 0;
// 	char *d;
// 	i = readline("asdasd: ");
// 	char **s;
// 	printf("%d\n", char_coun(i, 34));
// 	s = parsing_command(i, 32);
// 	while (s[a])
// 	{
// 		printf("%s\n", s[a]);
// 		a++;
// 	}
// }