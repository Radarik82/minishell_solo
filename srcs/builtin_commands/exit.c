/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denis <dprudnik@student.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 21:41:02 by denis             #+#    #+#             */
/*   Updated: 2026/05/23 21:41:15 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
