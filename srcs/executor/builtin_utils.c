/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprudnik <dprudnik@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 13:05:52 by dprudnik          #+#    #+#             */
/*   Updated: 2026/02/14 22:35:40 by dprudnik         ###   ########.fr       */
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
	// 	return (exec_cd(pipeline->cmds[0], shell));
	// else if (ft_strncmp(arg, "pwd", len) == 0)
	// 	return (exec_pwd(pipeline->cmds[0], shell));
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

// int	execute_builtin_with_redirection(t_cmd *cmd)
// {
// 	int	saved_stdin;
// 	int	saved_stdout;

// 	if (save_std_fds(&saved_stdin, &saved_stdout) == -1)
// 		return (1);

// 	if (apply_redirections(cmd) == -1)
// 	{
// 		restore_std_fds(saved_stdin, saved_stdout);
// 		return (1);
// 	}

// 	exec_builtin(cmd);

// 	restore_std_fds(saved_stdin, saved_stdout);
// 	return (0);
// }

