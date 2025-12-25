/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariazano <ariazano@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 00:31:23 by ariazano          #+#    #+#             */
/*   Updated: 2023/05/25 19:18:08 by ariazano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*result;
	void	*tmp;

	if (!lst || !f)
		return (NULL);
	result = NULL;
	while (lst)
	{
		tmp = (f)(lst->content);
		new = ft_lstnew(tmp);
		if (!new)
		{
			ft_lstclear(&result, del);
			del(tmp);
			return (NULL);
		}
		lst = lst->next;
		ft_lstadd_back(&result, new);
	}
	return (result);
}
