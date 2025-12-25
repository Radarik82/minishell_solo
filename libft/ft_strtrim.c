/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariazano <ariazano@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:58:46 by ariazano          #+#    #+#             */
/*   Updated: 2023/11/21 00:37:03 by ariazano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char *s1, char *set)
{
	unsigned char	start;
	unsigned char	i;
	unsigned char	len;
	char			*rlt;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	i = 0;
	len = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	if (start == len)
		return (ft_strdup(""));
	while (start < len && ft_strchr(set, s1[len]))
		len--;
	len = (len - start + 2);
	rlt = (char *)malloc(sizeof(char) * (len));
	if (!rlt)
		return (NULL);
	len -= 1;
	while (i < len)
		rlt[i++] = s1[start++];
	rlt[i] = '\0';
	return (rlt);
}
