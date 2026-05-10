/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleriaza <aleriaza@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 12:00:00 by aleriaza          #+#    #+#             */
/*   Updated: 2026/05/09 12:00:00 by aleriaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_redir_type(char *val)
{
	if (val[0] == '<' && val[1] == '<')
		return (REDIR_HEREDOC);
	if (val[0] == '<')
		return (REDIR_IN);
	if (val[0] == '>' && val[1] == '>')
		return (REDIR_APPEND);
	return (REDIR_OUT);
}

int	is_redir_op(char *val)
{
	if (!val || (val[0] != '<' && val[0] != '>'))
		return (0);
	return (val[1] == '\0' || (val[1] == val[0] && val[2] == '\0'));
}

t_redir	*new_redir(int type, char *file)
{
	t_redir	*node;

	node = malloc(sizeof(t_redir));
	if (!node)
		return (NULL);
	node->type = type;
	node->file = file;
	node->next = NULL;
	return (node);
}

void	redir_add_back(t_redir **head, t_redir *node)
{
	t_redir	*cur;

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

void	free_redirs(t_redir *head)
{
	t_redir	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->file)
			free(head->file);
		free(head);
		head = tmp;
	}
}
