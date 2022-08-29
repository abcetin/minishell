#include "minishell.h"

void lst_find(t_list **lst, void *data)
{
	if (!*lst)
		return;
	while (*lst)
	{
		if (ft_strstr((*lst)->content, data))
			break;
		(*lst) = (*lst)->next;
	}
}

// void	lst_clear(t_list **lst)
// {
// 	t_list	*temp;

// 	while (lst)
// 	{
// 		temp = (*lst)-> next;
// 		ft_lstdelone((*lst), free)
// 		(*lst) = temp;
// 	}
// }