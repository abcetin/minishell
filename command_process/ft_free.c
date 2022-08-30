#include "../minishell.h"

void ft_free_double(char **pointer)
{
	int i;

	i = 0;
	if (!pointer || !pointer)
		return;
	while (pointer[i])
	{
		free(pointer[i]);
		i++;
	}
	free(pointer);
}

void ft_free_int(int **pointer, int count)
{
	int i;

	i = 0;
	while (i <= count)
		free(pointer[i++]);
	free(pointer);
}