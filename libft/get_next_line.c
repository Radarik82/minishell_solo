/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariazano <ariazano@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:14:40 by ariazano          #+#    #+#             */
/*   Updated: 2023/12/05 22:18:07 by ariazano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_gnl(char *rest_of_line)
{
	int		i;
	char	*str;

	i = 0;
	if (!rest_of_line[i])
		return (NULL);
	while (rest_of_line[i] && rest_of_line[i] != '\n')
		i++;
	str = (char *)malloc((sizeof(char) * (i + 1 + (rest_of_line[i] == '\n'))));
	if (!str)
		return (free(str), NULL);
	i = 0;
	while (rest_of_line[i] && rest_of_line[i] != '\n')
	{
		str[i] = rest_of_line[i];
		i++;
	}
	if (rest_of_line[i] == '\n')
	{
		str[i] = rest_of_line[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_refresh_rest(char *rest_of_line)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (rest_of_line[i] && rest_of_line[i] != '\n')
		i++;
	if (!rest_of_line[i])
		return (free(rest_of_line), NULL);
	i++;
	str = (char *)malloc(sizeof(char) * (ft_strlen(rest_of_line) *(i + 1)));
	if (!str)
		return (free (rest_of_line), free(str), NULL);
	j = 0;
	while (rest_of_line[i])
		str[j++] = rest_of_line[i++];
	str[j] = '\0';
	return (free (rest_of_line), str);
}

char	*ft_line_to_rest(int fd, char *rest_of_line)
{
	char	*buff;
	int		bytes_read;

	bytes_read = 1;
	buff = (char *)malloc((BUFFER_SIZE) * sizeof(char));
	if (!buff)
		return (free(buff), free(rest_of_line), NULL);
	while (!ft_strchr(rest_of_line, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buff), free(rest_of_line), NULL);
		buff[bytes_read] = '\0';
		rest_of_line = gnl_strjoin(rest_of_line, buff);
		if (!rest_of_line || !buff)
			return (free(rest_of_line), free(buff), NULL);
	}
	return (free(buff), rest_of_line);
}

char	*get_next_line(int fd)
{
	char			*current_line;
	static char		*rest_of_line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	rest_of_line = ft_line_to_rest(fd, rest_of_line);
	if (!rest_of_line)
		return (free (rest_of_line), NULL);
	current_line = ft_gnl(rest_of_line);
	if (!current_line)
	{
		free(rest_of_line);
		rest_of_line = NULL;
		return (NULL);
	}
	rest_of_line = ft_refresh_rest(rest_of_line);
	return (current_line);
}
