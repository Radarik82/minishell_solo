/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleriaza <aleriaza@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 15:20:22 by aleriaza          #+#    #+#             */
/*   Updated: 2026/02/09 19:37:30 by aleriaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	process_segments(char *input, char **segments, int pipe_count)
{
	int	idx;
	int	start;
	int	end;

	idx = 0;
	start = 0;
	while (idx <= pipe_count)
	{
		end = find_pipe_pos(input, start);
		segments[idx] = extract_segment(input, start, end);
		if (!segments[idx])
			return (-1);
		start = end + 1;
		idx++;
	}
	segments[idx] = NULL;
	return (0);
}
