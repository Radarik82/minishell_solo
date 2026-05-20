/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diagnostic_printout.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprudnik <dprudnik@student.42wolfsburg.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 14:26:27 by dprudnik          #+#    #+#             */
/*   Updated: 2026/05/18 14:39:20 by dprudnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Helpers
*/

static const char	*redir_type_str(int type)
{
	if (type == REDIR_IN)
		return ("<");
	if (type == REDIR_OUT)
		return (">");
	if (type == REDIR_APPEND)
		return (">>");
	if (type == REDIR_HEREDOC)
		return ("<<");
	return ("UNKNOWN");
}

static void	print_args(char **args)
{
	int	i;

	if (!args || !args[0])
	{
		printf("    args        : (none)\n");
		return ;
	}
	printf("    args        :\n");
	i = 0;
	while (args[i])
	{
		printf("      [%d] \"%s\"\n", i, args[i]);
		i++;
	}
}

static void	print_redirs(t_redir *redir)
{
	int	i;

	if (!redir)
	{
		printf("    redirections: (none)\n");
		return ;
	}
	printf("    redirections:\n");
	i = 0;
	while (redir)
	{
		printf("      [%d] %-2s  \"%s\"\n",
			i,
			redir_type_str(redir->type),
			redir->file);
		redir = redir->next;
		i++;
	}
}

/*
** Main diagnostic printout
*/

void	diagnostic_printout(t_cmd *cmd)
{
	int		cmd_index;
	t_cmd	*current;

	if (!cmd)
	{
		printf("========== PARSER DEBUG ==========\n");
		printf("No commands parsed.\n");
		printf("==================================\n");
		return ;
	}
	printf("\n");
	printf("========== PARSER DEBUG ==========\n");
	current = cmd;
	cmd_index = 0;
	while (current)
	{
		printf("Command #%d\n", cmd_index);
		printf("  --------------------------------\n");
		print_args(current->args);
		print_redirs(current->redirs);
		if (current->next)
			printf("    pipe        : yes\n");
		else
			printf("    pipe        : no\n");
		printf("\n");
		current = current->next;
		cmd_index++;
	}
	printf("==================================\n");
}
