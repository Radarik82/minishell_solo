/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprudnik <dprudnik@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 15:20:22 by aleriaza          #+#    #+#             */
/*   Updated: 2026/01/23 18:26:23 by dprudnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	**split_by_pipes(char *input)
// {
// 	char	**segments;
// 	int		count;
// 	int		i;
// 	int		pos;

// 	count = count_pipes(input) + 1;
// 	segments = malloc(sizeof(char *) * (count + 1));
// 	if (!segments)
// 		return (NULL);
// 	i = 0;
// 	pos = 0;
// 	while (i < count)
// 	{
// 		segments[i] = get_next_segment(input, &pos);
// 		if (!segments[i])
// 		{
// 			free_array(segments);
// 			return (NULL);
// 		}
// 		i++;
// 	}
// 	segments[count] = NULL;
// 	return (segments);
// }
