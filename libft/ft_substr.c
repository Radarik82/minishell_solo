/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariazano <ariazano@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:26:24 by ariazano          #+#    #+#             */
/*   Updated: 2023/11/21 00:35:21 by ariazano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	if (s == 0)
		return (NULL);
	if (start < ft_strlen(s))
	{
		if (len >= (ft_strlen(s) - start))
			str = malloc(sizeof(char) * (ft_strlen(s) - start) + 1);
		else
			str = malloc((sizeof(char) * len) + 1);
		if (str == NULL)
			return (NULL);
		while (i < len && s[start])
			str[i++] = (char)s[start++];
	}
	else
	{
		str = malloc(1);
		if (str == NULL)
			return (NULL);
	}
	str[i] = '\0';
	return (str);
}
