/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprudnik <dprudnik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 13:05:52 by dprudnik          #+#    #+#             */
/*   Updated: 2026/02/19 16:11:55 by dprudnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *arg)
{
	int	len;

	len = ft_strlen(arg);
	if (ft_strncmp(arg, "echo", len) == 0 ||
		ft_strncmp(arg, "cd", len) == 0 ||
		ft_strncmp(arg, "pwd", len) == 0 ||
		ft_strncmp(arg, "export", len) == 0 ||
		ft_strncmp(arg, "unset", len) == 0 ||
		ft_strncmp(arg, "env", len) == 0 ||
		ft_strncmp(arg, "exit", len) == 0)
		return (1);
	return	(0);
}

int	execute_builtin(t_pipeline *p, t_cmd *cmd, t_shell *shell)
{
	int	len;
	char *arg;

	arg = cmd->args[0];
	len = ft_strlen(arg);
	if (ft_strncmp(arg, "echo", len) == 0)
		return (exec_echo(cmd->args));
	// else if (ft_strncmp(arg, "cd", len) == 0)
	// 	return (exec_cd(cmd, shell));
	else if (ft_strncmp(arg, "pwd", len) == 0)
		return (exec_pwd(cmd, shell));
	// else if (ft_strncmp(arg, "export", len) == 0)
	// 	return (exec_export(pipeline->cmds[0], shell));
	// else if (ft_strncmp(arg, "unset", len) == 0)
	// 	return (exec_unset(pipeline->cmds[0], shell));
	else if (ft_strncmp(arg, "env", len) == 0)
		return (exec_env(shell));
	else if (ft_strncmp(arg, "exit", len) == 0)
		return (exec_exit(p, cmd, shell));
	return (1);
}


