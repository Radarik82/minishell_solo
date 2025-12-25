/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariazano <ariazano@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:43:18 by ariazano          #+#    #+#             */
/*   Updated: 2023/11/21 00:34:21 by ariazano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	char	*s;
	size_t	count;

	count = ft_strlen(src);
	s = malloc(count * sizeof(char) + 1);
	if (s == NULL)
		return (NULL);
	ft_strlcpy(s, src, count + 1);
	return (s);
}
