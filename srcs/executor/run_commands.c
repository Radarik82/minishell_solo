/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleriaza <aleriaza@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 16:43:43 by aleriaza          #+#    #+#             */
/*   Updated: 2026/05/12 17:24:27 by dprudnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_commands(t_cmd *cmds, t_shell *shell)
{
	//need to handle expander "$" here. (I think).
	if (cmds->next == NULL && is_builtin(cmds->args[0]))
		execute_builtin(cmds, shell);
	else //if (cmds->next == NULL)// Only for single extern arg to bypass pipecreation
		execute_command(cmds->args, shell);
	// else
	// 	execute_multi_cmds(cmds, shell);
	return ;
	// command_readout(pipeline, shell);//Debug Only
}

// // TODO : make fit new data structure.
// // TODO : need to handle return exit codes and functions need
// // to be changed to return proper exit codes.
int	execute_builtin(t_cmd *cmd, t_shell *shell)
{
	int	len;
	char *arg;

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
	return (1);
}

char	*get_exit_status(t_shell *shell)
{
	return ft_itoa(shell->exit_status);
}
//
// // FIX : copied from old V1.0!!!
// static int	handle_parent(t_exec *exec)
// {
// 	if (exec->prev_fd != -1)
// 		close(exec->prev_fd);
// 	if (exec->i < exec->p->cmd_count - 1)
// 	{
// 		close(exec->pipefd[1]);
// 		return (exec->pipefd[0]);
// 	}
// 	return (-1);
// }
//
// // FIX : copied from old V1.0!!!
// static void	exec_child(t_exec *exec)
// {
// 	if (exec->prev_fd != -1)
// 		dup2(exec->prev_fd, STDIN_FILENO);
// 	if (exec->i < exec->p->cmd_count - 1)
// 		dup2(exec->pipefd[1], STDOUT_FILENO);
// 	if (exec->prev_fd != -1)
// 		close(exec->prev_fd);
// 	if (exec->i < exec->p->cmd_count - 1)
// 	{
// 		close(exec->pipefd[0]);
// 		close(exec->pipefd[1]);
// 	}
// 	execute_child(exec->p->cmds[exec->i]->args,
// 		exec->shell->env);
// }
//
// // FIX : copied from old V1.0!!!
// static void wait_children(int cmd_count, pid_t last_pid, t_shell *shell)
// {
// 	int		i;
// 	int		status;
// 	pid_t	pid;
//
// 	i = 0;
// 	while (i < cmd_count)
// 	{
// 		pid = waitpid(-1, &status, 0);
// 		if (pid == last_pid)
// 		{
// 			if (WIFEXITED(status))
// 				shell->exit_status = WEXITSTATUS(status);
// 			else if (WIFSIGNALED(status))
// 				shell->exit_status = 128 + WTERMSIG(status);
// 		}
// 		i++;
// 	}
// }
//
// // TODO : change fucntionality to fit new data structure.
// // FIX : copied from old V1.0!!!
// int	execute_multi_cmds(t_cmd *cmds, t_shell *shell)
// {
// 	t_exec	exec;
// 	pid_t	pid;
// 	pid_t	last_pid;
//
// 	exec.shell = shell;
// 	exec.i = 0;
// 	exec.prev_fd = -1;
// 	while (exec.i < p->cmd_count)
// 	{
// 		if (exec.i < p->cmd_count - 1)
// 			pipe(exec.pipefd);
// 		pid = fork();
// 		if (pid == 0)
// 			exec_child(&exec);
// 		if (exec.i == p->cmd_count - 1)
// 			last_pid = pid;
// 		exec.prev_fd = handle_parent(&exec);
// 		exec.i++;
// 	}
// 	wait_children(p->cmd_count, last_pid, shell);
// 	return (0);
// }
