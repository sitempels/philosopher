/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:24:48 by stempels          #+#    #+#             */
/*   Updated: 2025/03/24 15:19:33 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(int), void (*del)(int))
{
	t_list	*new_node;
	t_list	*new_lst;
	int		new_content;

	if (!lst)
		return (NULL);
	new_lst = NULL;
	while (lst)
	{
		if (f)
			new_content = f(lst -> content);
		else
			new_content = lst -> content;
		new_node = ft_lstnew(new_content);
		if (!new_node)
		{
			ft_lstclear(&new_lst, del);
			if (f)
				del(new_content);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, new_node);
		lst = lst -> next;
	}
	return (new_lst);
}
