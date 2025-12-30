/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleriaza <aleriaza@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 15:09:35 by aleriaza          #+#    #+#             */
/*   Updated: 2025/12/29 15:34:02 by aleriaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_pipe(char c)
{
	return (c == '|');
}

int	count_pipes(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (is_pipe(str[i]))
			count++;
		i++;
	}
	return (count);
}

int	find_pipe_pos(char *input, int start)
{
	int	i;

	i = start;
	while (input[i])
	{
		if (is_pipe(input[i]))
			return (i);
		i++;
	}
	return (i);
}

char	*extract_segment(char *input, int start, int end)
{
	char	*segment;
	int		len;
	int		i;

	len = end - start;
	segment = malloc(sizeof(char) * (len + 1));
	if (!segment)
		return (NULL);
	i = 0;
	while (i < len)
	{
		segment[i] = input[start + i];
		i++;
	}
	segment[i] = '\0';
	return (segment);
}

char	*get_next_segment(char *input, int *pos)
{
	int		start;
	int		end;
	char	*segment;

	start = *pos;
	end = find_pipe_pos(input, start);
	segment = extract_segment(input, start, end);
	*pos = end + 1;
	return (segment);
}
