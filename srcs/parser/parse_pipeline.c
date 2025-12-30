/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleriaza <aleriaza@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 15:23:06 by aleriaza          #+#    #+#             */
/*   Updated: 2025/12/30 13:56:17 by aleriaza         ###   ########.fr       */
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

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->args)
		free_array(cmd->args);
	free(cmd);
}

t_cmd	*parse_one_segment(char *segment)
{
	char	**tokens;
	t_cmd	*cmd;

	if (is_empty_segment(segment))
		return (NULL);
	tokens = tokenize_input(segment);
	if (!tokens)
		return (NULL);
	cmd = create_cmd(tokens);
	return (cmd);
}

t_pipeline	*alloc_pipeline(int count)
{
	t_pipeline	*pipeline;

	pipeline = malloc(sizeof(t_pipeline));
	if (!pipeline)
		return (NULL);
	pipeline->cmd_count = count;
	pipeline->cmds = malloc(sizeof(t_cmd *) * (count + 1));
	if (!pipeline->cmds)
	{
		free(pipeline);
		return (NULL);
	}
	return (pipeline);
}
