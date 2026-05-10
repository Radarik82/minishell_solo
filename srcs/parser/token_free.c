/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleriaza <aleriaza@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 12:00:00 by aleriaza          #+#    #+#             */
/*   Updated: 2026/05/09 12:00:00 by aleriaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	token_count(t_token *head)
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

char	**tokens_to_argv(t_token *head)
{
	char	**argv;
	int		size;
	int		i;

	size = token_count(head);
	argv = malloc(sizeof(char *) * (size + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (head)
	{
		argv[i] = ft_strdup(head->val);
		if (!argv[i])
		{
			free_array(argv);
			return (NULL);
		}
		i++;
		head = head->next;
	}
	argv[i] = NULL;
	return (argv);
}

void	free_tokens(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->val)
			free(head->val);
		free(head);
		head = tmp;
	}
}
