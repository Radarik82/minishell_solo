/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariazano <ariazano@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 00:43:07 by ariazano          #+#    #+#             */
/*   Updated: 2023/05/21 16:09:45 by ariazano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*nextelem;

	if (lst && del)
	{
		tmp = *lst;
		while (tmp)
		{
			nextelem = tmp->next;
			ft_lstdelone(tmp, del);
			tmp = nextelem;
		}
		*lst = NULL;
	}
}
