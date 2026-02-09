/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleriaza <aleriaza@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 17:20:08 by aleriaza          #+#    #+#             */
/*   Updated: 2026/02/09 19:37:32 by aleriaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_word_len(char *str, int start)
{
	int	len;

	len = 0;
	while (str[start + len] && !is_space(str[start + len]))
		len++;
	return (len);
}

char	*extract_word(char *str, int start, int len)
{
	char	*word;
	int		i;

	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = str[start + i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

int	count_words(char *str)
{
	int	count;
	int	i;
	int	in_word;

	count = 0;
	i = 0;
	in_word = 0;
	while (str[i])
	{
		if (!is_space(str[i]) && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (is_space(str[i]))
			in_word = 0;
		i++;
	}
	return (count);
}

char	**tokenize_input(char *input)
{
	char	**tokens;
	int		word_count;

	if (!input)
		return (NULL);
	word_count = count_words(input);
	tokens = malloc(sizeof(char *) * (word_count + 1));
	if (!tokens)
		return (NULL);
	if (process_tokens(input, tokens) == -1)
	{
		free_array(tokens);
		return (NULL);
	}
	return (tokens);
}
