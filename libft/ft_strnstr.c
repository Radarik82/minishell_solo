/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariazano <ariazano@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:26:24 by ariazano          #+#    #+#             */
/*   Updated: 2023/11/24 02:59:58 by ariazano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char	*haystack, char *niddle, size_t n)
{
	size_t	i;
	size_t	j;

	if (!*niddle)
		return ((char *)haystack);
	j = 0;
	while (haystack[j])
	{
		i = 0;
		while (haystack[j + i] == niddle[i] && j + i < n)
		{
			if (!niddle[1 + i])
			{
				return ((char *)(haystack + j));
			}
			i++;
		}
		j++;
	}
	return (NULL);
}
