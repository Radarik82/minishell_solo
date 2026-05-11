/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprudnik <dprudnik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 16:43:43 by aleriaza          #+#    #+#             */
/*   Updated: 2026/02/19 16:21:23 by dprudnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

// TODO: need to handle expander "$" here. (I think).
void	run_pipeline(t_pipeline *pipeline, t_shell *shell)
{
	if (pipeline->cmd_count == 1 && is_builtin(pipeline->cmds[0]->args[0]))
		execute_builtin(pipeline, pipeline->cmds[0], shell);
	else if (pipeline->cmd_count == 1)// Only for single extern arg to bypass pipecreation
		execute_command(pipeline->cmds[0]->args, shell);
	else
		execute_multi_cmds(pipeline, shell);
	return ;
	// command_readout(pipeline, shell);//Debug Only
}

static int	handle_parent(t_exec *exec)
{
	if (exec->prev_fd != -1)
		close(exec->prev_fd);
	if (exec->i < exec->p->cmd_count - 1)
	{
		close(exec->pipefd[1]);
		return (exec->pipefd[0]);
	}
	return (-1);
}

static void	exec_child(t_exec *exec)
{
	if (exec->prev_fd != -1)
		dup2(exec->prev_fd, STDIN_FILENO);
	if (exec->i < exec->p->cmd_count - 1)
		dup2(exec->pipefd[1], STDOUT_FILENO);
	if (exec->prev_fd != -1)
		close(exec->prev_fd);
	if (exec->i < exec->p->cmd_count - 1)
	{
		close(exec->pipefd[0]);
		close(exec->pipefd[1]);
	}
	execute_child(exec->p->cmds[exec->i]->args,
		exec->shell->env);
}

static void wait_children(int cmd_count, pid_t last_pid, t_shell *shell)
{
	int		i;
	int		status;
	pid_t	pid;

	i = 0;
	while (i < cmd_count)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				shell->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				shell->exit_status = 128 + WTERMSIG(status);
		}
		i++;
	}
}

int	execute_multi_cmds(t_pipeline *p, t_shell *shell)
{
	t_exec	exec;
	pid_t	pid;
	pid_t	last_pid;

	exec.p = p;
	exec.shell = shell;
	exec.i = 0;
	exec.prev_fd = -1;
	while (exec.i < p->cmd_count)
	{
		if (exec.i < p->cmd_count - 1)
			pipe(exec.pipefd);
		pid = fork();
		if (pid == 0)
			exec_child(&exec);
		if (exec.i == p->cmd_count - 1)
			last_pid = pid;
		exec.prev_fd = handle_parent(&exec);
		exec.i++;
	}
	wait_children(p->cmd_count, last_pid, shell);
	return (0);
}
