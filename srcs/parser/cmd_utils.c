/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleriaza <aleriaza@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 12:00:00 by aleriaza          #+#    #+#             */
/*   Updated: 2026/05/09 12:00:00 by aleriaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*create_cmd(char **args)
{
	t_cmd	*cmd;

	if (!args)
		return (NULL);
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = args;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	cmd_add_back(t_cmd **head, t_cmd *node)
{
	t_cmd	*cur;

	if (!head || !node)
		return ;
	if (!*head)
	{
		*head = node;
		return ;
	}
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = node;
}

int	cmd_count(t_cmd *head)
{
	int	n;

	n = 0;
	while (head)
	{
		n++;
		head = head->next;
	}
	return (n);
}

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->args)
		free_array(cmd->args);
	if (cmd->redirs)
		free_redirs(cmd->redirs);
	free(cmd);
}

void	free_cmd_list(t_cmd *head)
{
	t_cmd	*tmp;

	while (head)
	{
		tmp = head->next;
		free_cmd(head);
		head = tmp;
	}
}
