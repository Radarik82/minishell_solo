/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleriaza <aleriaza@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 13:56:58 by aleriaza          #+#    #+#             */
/*   Updated: 2026/02/09 19:39:18 by aleriaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_empty_segment(char *segment)
{
	int	i;

	if (!segment)
		return (1);
	i = 0;
	while (segment[i])
	{
		if (!is_space(segment[i]))
			return (0);
		i++;
	}
	return (1);
}

t_cmd	*create_cmd(char **args)
{
	t_cmd	*cmd;

	if (!args)
		return (NULL);
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = args;
	return (cmd);
}
