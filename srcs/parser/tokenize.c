/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleriaza <aleriaza@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 17:20:08 by aleriaza          #+#    #+#             */
/*   Updated: 2026/05/09 12:00:00 by aleriaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_word_len(char *str, int i)
{
	int	start;
	int	ret;

	start = i;
	while (str[i] && !is_space(str[i]) && str[i] != '<' && str[i] != '>')
	{
		if (is_quote(str[i]))
		{
			ret = jump_past_quote(str, i);
			if (ret == -1)
				return (-1);
			i = ret;
		}
		else
			i++;
	}
	return (i - start);
}

static char	*extract_word(char *str, int start, int len)
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

static char	*get_redir_op(char *str, int *i)
{
	char	*op;

	if ((str[*i] == '<' && str[*i + 1] == '<')
		|| (str[*i] == '>' && str[*i + 1] == '>'))
	{
		op = ft_substr(str, *i, 2);
		*i += 2;
	}
	else
	{
		op = ft_substr(str, *i, 1);
		*i += 1;
	}
	return (op);
}

static int	add_next_token(char *input, int *i, t_token **head)
{
	char	*word;
	t_token	*node;
	int		wlen;

	if (input[*i] == '<' || input[*i] == '>')
		word = get_redir_op(input, i);
	else
	{
		wlen = get_word_len(input, *i);
		if (wlen == -1)
			return (-1);
		word = extract_word(input, *i, wlen);
		*i += wlen;
	}
	if (!word)
		return (-1);
	node = new_token(word);
	if (!node)
		return (free(word), -1);
	token_add_back(head, node);
	return (0);
}

t_token	*tokenize_input(char *input)
{
	t_token	*head;
	int		i;

	if (!input)
		return (NULL);
	head = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] && is_space(input[i]))
			i++;
		if (!input[i])
			break ;
		if (add_next_token(input, &i, &head) == -1)
		{
			free_tokens(head);
			return (NULL);
		}
	}
	return (head);
}
