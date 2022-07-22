#include "minishell.h"

static char *ft_strdup2(char *str, unsigned int size)
{
	char *ret;

	ret = malloc(size);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, str, ft_strlen(str) + 1);
	return (ret);
}

void    *ft_realloc(void *ptr, unsigned int new_size)
{
    char	*new_ptr;
	char	*old_ptr;

	//printf("%ld\n",sizeof(ptr) / sizeof(*ptr));
	old_ptr = (char *)ptr;
    if (ptr == NULL)
        return (malloc(new_size));
    new_ptr = ft_strdup2(old_ptr, new_size);
	//free(old_ptr);
	return (new_ptr);
}