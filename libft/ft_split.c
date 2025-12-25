/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariazano <ariazano@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 19:33:16 by ariazano          #+#    #+#             */
/*   Updated: 2023/11/21 00:40:52 by ariazano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

static char	**ft_freemem(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (NULL);
}

static char	**ft_fillarr(char *s, char c, int words, char **result)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	while (j < words)
	{
		while (s[i] == c)
			i++;
		len = 0;
		while (s[i] != c && s[i])
		{
			len++;
			i++;
		}
		result[j] = ft_substr(s, i - len, len);
		if (result[j] == NULL)
			return (ft_freemem(result));
		j++;
	}
	result[j] = NULL;
	return (result);
}

char	**ft_split(char *s, char c)
{
	char	**result;
	int		words;

	if (s == NULL)
		return (NULL);
	words = ft_count_words(s, c);
	result = ft_calloc((words + 1), sizeof(char *));
	if (result == NULL)
		return (NULL);
	return (ft_fillarr(s, c, words, result));
}
