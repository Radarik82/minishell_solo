/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprudnik <dprudnik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 16:43:43 by aleriaza          #+#    #+#             */
/*   Updated: 2026/05/22 15:34:37 by dprudnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_commands(t_cmd *cmds, t_shell *shell)
{
	if (cmds->next == NULL && is_builtin(cmds->args[0]))
		execute_builtin(cmds, shell);
	else if (cmds->next == NULL)
		execute_command(cmds, shell);
	else
		execute_pipeline(cmds, shell);
}

int	execute_builtin(t_cmd *cmd, t_shell *shell)
{
	int	exit_code;
	int	saved_stdin;
	int	saved_stdout;

	exit_code = 0;
	if (cmd->redirs == NULL)
		exit_code = select_builtin(cmd, shell);
	else
	{
		if (save_std_fds(&saved_stdin, &saved_stdout) == -1)
		{
			shell->exit_status = 1;
			return (-1);
		}
		apply_redirections(cmd->redirs);
		exit_code = select_builtin(cmd, shell);
		restore_std_fds(saved_stdin, saved_stdout);
	}
	shell->exit_status = exit_code;
	return (0);
}

int	select_builtin(t_cmd *cmd, t_shell *shell)
{
	int		len;
	char	*arg;

	arg = cmd->args[0];
	len = ft_strlen(arg);
	if (ft_strncmp(arg, "echo", len) == 0)
		return (exec_echo(cmd->args));
	else if (ft_strncmp(arg, "cd", len) == 0)
		return (exec_cd(cmd, shell));
	else if (ft_strncmp(arg, "pwd", len) == 0)
		return (exec_pwd(cmd, shell));
	else if (ft_strncmp(arg, "export", len) == 0)
		return (exec_export(cmd, shell));
	else if (ft_strncmp(arg, "unset", len) == 0)
		return (exec_unset(cmd, shell));
	else if (ft_strncmp(arg, "env", len) == 0)
		return (exec_env(shell));
	else if (ft_strncmp(arg, "exit", len) == 0)
		return (exec_exit(cmd, shell));
	return (0);
}
