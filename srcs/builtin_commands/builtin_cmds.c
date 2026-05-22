/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprudnik <dprudnik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:32:39 by aleriaza          #+#    #+#             */
/*   Updated: 2026/05/22 16:00:02 by dprudnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Print all exported vars in declare -x format (export with no args) */
static void	exec_export_no_args(t_var *vars)
{
	while (vars)
	{
		if (vars->exported)
			ft_printf("declare -x %s=\"%s\"\n", vars->name, vars->value);
		vars = vars->next;
	}
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

/* Remove variables from the shell var list */
int	exec_unset(t_cmd *cmd, t_shell *shell)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		unset_var(cmd->args[i], shell);
		i++;
	}
	return (0);
}

/* Exit the shell with optional exit code */
int	exec_exit(t_cmd *cmd, t_shell *shell)
{
	int	exit_code;

	if (shell->in_child == 0)
		write(1, "exit\n", 5);
	exit_code = shell->exit_status;
	if (cmd->args[1] && cmd->args[2])
	{
		print_error("exit: too many arguments");
		free_cmd_list(cmd);
		if (shell->vars)
			free_vars(shell->vars);
		exit(1);
	}
	if (cmd->args[1])
		exit_code = ft_atoi(cmd->args[1]);
	free_cmd_list(cmd);
	if (shell->vars)
		free_vars(shell->vars);
	exit(exit_code);
}
