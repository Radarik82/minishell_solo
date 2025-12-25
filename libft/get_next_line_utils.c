/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariazano <ariazano@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 00:24:45 by ariazano          #+#    #+#             */
/*   Updated: 2023/11/21 00:33:14 by ariazano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*gnl_strjoin(char *rest_of_line, char *buff)
{
	unsigned int	len;
	char			*str;

	if (!rest_of_line)
	{
		rest_of_line = (char *)malloc(1 * sizeof(char) + 1);
		if (!rest_of_line)
			return (NULL);
		rest_of_line[0] = '\0';
	}
	if (!rest_of_line || !buff)
		return (NULL);
	len = ft_strlen(rest_of_line) + ft_strlen(buff);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (free (rest_of_line), free(str), NULL);
	ft_strcpy(str, rest_of_line);
	len = ft_strlen(rest_of_line);
	ft_strcpy(&str[len], buff);
	return (free(rest_of_line), str);
}
