/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory_allocation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acetin <acetin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 09:53:28 by acetin            #+#    #+#             */
/*   Updated: 2022/09/07 12:12:23 by acetin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_double(char **pointer)
{
	int	i;

	i = 0;
	if (!*pointer)
		return ;
	while (pointer[i])
	{
		free(pointer[i]);
		i++;
	}
	free(pointer);
}

void	ft_free_int(int **pointer, int count)
{
	int	i;

	i = 0;
	while (i <= count)
		free(pointer[i++]);
	free(pointer);
}

void	*ft_realloc(void *ptr, size_t size)
{
	char	*new_ptr;

	if (!ptr)
		return (malloc(size));
	new_ptr = malloc(size);
	ft_memmove(new_ptr, ptr, size);
	free(ptr);
	return (new_ptr);
}
