#include "../minishell.h"

int is_alnum(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int ft_strchr2(char *s, int c)
{
	int i;

	i = 0;
	while (s[i] != '\0' && (char)c != s[i])
		i++;;
	if ((char)c == s[i])
		return (1);
	return (0);
}

int is_exist_file(char *path)
{
	if (access(path, F_OK) == -1)
		return (0);
	return (1);
}

int open_file(char *path)
{
	int fd;

	if (!path)
		return (-1);
	if (!is_exist_file(path))
		fd = open(path, O_RDWR | O_CREAT);
	else
		fd = open(path, O_APPEND | O_RDWR);
	if (fd == -1)
	{
		perror("");
		return (0);
	}
	return (fd);
}

void clear_file(char *path)
{
	int fd;
	fd = open(path, O_TRUNC);
	if (fd < 0)
		perror("");
	close(fd);
}
