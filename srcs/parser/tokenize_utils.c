/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleriaza <aleriaza@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 18:55:47 by aleriaza          #+#    #+#             */
/*   Updated: 2026/02/09 19:37:31 by aleriaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

int	process_tokens(char *input, char **tokens)
{
	int	i;
	int	j;
	int	word_len;

	i = 0;
	j = 0;
	while (input[i])
	{
		while (input[i] && is_space(input[i]))
			i++;
		if (!input[i])
			break ;
		word_len = get_word_len(input, i);
		tokens[j] = extract_word(input, i, word_len);
		if (!tokens[j])
			return (-1);
		j++;
		i += word_len;
	}
	tokens[j] = NULL;
	return (0);
}
