/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acetin <acetin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 09:55:02 by acetin            #+#    #+#             */
/*   Updated: 2022/09/07 09:55:57 by acetin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lst_find(t_list **lst, void *data)
{
	int	i;
	int	size;

	size = ft_lstsize(*lst);
	i = 0;
	if (!*lst)
		return (0);
	while (*lst)
	{
		if (ft_strstr((*lst)->content, data)
			|| !ft_strncmp((*lst)->content, data, ft_strlen(data)))
			(*lst) = (*lst)->next;
		else
			break ;
		i++;
	}
	if (size == i)
		return (1);
	return (0);
}

void	add_to_list(char **temp, t_list **cmd)
{
	int	i;

	i = 1;
	while (temp[i])
		ft_lstadd_back(cmd, ft_lstnew(ft_strdup(temp[i++])));
}

void	lstclear(t_list **lst)
{
	t_list	*tmp;

	while (*lst)
	{
		tmp = (*lst);
		(*lst) = (*lst)->next;
		free(tmp->content);
		free(tmp);
	}
}
