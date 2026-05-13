/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleriaza <aleriaza@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 12:00:00 by aleriaza          #+#    #+#             */
/*   Updated: 2026/05/09 12:00:00 by aleriaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token	*remove_token(t_token **head, t_token *prev, t_token *cur)
{
	t_token	*next;

	next = cur->next;
	if (prev)
		prev->next = next;
	else
		*head = next;
	cur->next = NULL;
	free(cur->val);
	free(cur);
	return (next);
}

static int	extract_one_redir(t_token **head, t_token **prev_p,
				t_token *cur, t_redir **redirs)
{
	int		type;
	t_token	*file_tok;
	t_redir	*redir;

	type = get_redir_type(cur->val);
	cur = remove_token(head, *prev_p, cur);
	file_tok = cur;
	if (!file_tok)
		return (-1);
	redir = new_redir(type, ft_strdup(file_tok->val));
	if (!redir)
		return (-1);
	redir_add_back(redirs, redir);
	remove_token(head, *prev_p, file_tok);
	return (0);
}

int	parse_redirs(t_token **head, t_redir **redirs)
{
	t_token	*cur;
	t_token	*prev;

	cur = *head;
	prev = NULL;
	while (cur)
	{
		if (is_redir_op(cur->val))
		{
			if (extract_one_redir(head, &prev, cur, redirs) == -1)
				return (-1);
			cur = (prev ? prev->next : *head);
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
	return (0);
}
