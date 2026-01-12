/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleriaza <aleriaza@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 15:23:06 by aleriaza          #+#    #+#             */
/*   Updated: 2026/01/12 16:32:58 by aleriaza         ###   ########.fr       */
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

/* Create pipeline from segments */
t_pipeline	*create_pipeline(char **segments)
{
	t_pipeline	*pipeline;
	int			i;

	pipeline = malloc(sizeof(t_pipeline));
	if (!pipeline)
		return (NULL);
	pipeline->cmd_count = array_len(segments);
	pipeline->cmds = malloc(sizeof(t_cmd *) * (pipeline->cmd_count + 1));
	if (!pipeline->cmds)
	{
		free(pipeline);
		return (NULL);
	}
	i = 0;
	while (segments[i])
	{
		pipeline->cmds[i] = create_cmd(tokenize_input(segments[i]));
		i++;
	}
	pipeline->cmds[i] = NULL;
	return (pipeline);
}

/* Free entire pipeline */
void	free_pipeline(t_pipeline *pipeline)
{
	int	i;

	if (!pipeline)
		return ;
	if (pipeline->cmds)
	{
		i = 0;
		while (i < pipeline->cmd_count)
		{
			free_cmd(pipeline->cmds[i]);
			i++;
		}
		free(pipeline->cmds);
	}
	free(pipeline);
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
