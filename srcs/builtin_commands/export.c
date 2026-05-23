/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprudnik <dprudnik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:32:39 by aleriaza          #+#    #+#             */
/*   Updated: 2026/05/23 21:47:09 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Print all exported vars in declare -x format (export with no args) */
static void	exec_export_no_args(t_var *vars)
{
	t_var	**arr;
	int		size;
	int		i;

	arr = vars_to_array(vars, &size);
	if (!arr)
		return ;
	i = 0;
	while (i < size)
	{
		if (arr[i]->exported)
			print_export_var(arr[i]);
		i++;
	}
	free(arr);
}

static void	process_export_arg(char *arg, t_shell *shell)
{
	t_var	*node;
	char	*eq;

	eq = ft_strchr(arg, '=');
	if (eq)
	{
		*eq = '\0';
		set_var(arg, eq + 1, 1, shell);
		*eq = '=';
	}
	else
	{
		node = find_var(arg, shell->vars);
		if (node)
			node->exported = 1;
		else
			set_var(arg, NULL, 1, shell);
	}
}

/* Set or create vars as exported; no args prints current exported vars */
int	exec_export(t_cmd *cmd, t_shell *shell)
{
	int	i;

	if (!cmd->args[1])
		return (exec_export_no_args(shell->vars), 0);
	i = 1;
	while (cmd->args[i])
	{
		process_export_arg(cmd->args[i], shell);
		i++;
	}
	return (0);
}
