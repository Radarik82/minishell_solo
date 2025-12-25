/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariazano <ariazano@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 11:37:51 by ariazano          #+#    #+#             */
/*   Updated: 2023/05/27 13:50:50 by ariazano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char		*tmp_dst;
	const char	*tmp_src;

	tmp_dst = dst;
	tmp_src = src;
	if (dst == src)
		return (dst);
	if (tmp_src < tmp_dst)
	{
		while (n--)
			tmp_dst[n] = tmp_src[n];
	}
	else
	{
		while (n--)
			*tmp_dst++ = *tmp_src++;
	}
	return (dst);
}
