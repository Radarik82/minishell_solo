/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprudnik <dprudnik@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 16:43:43 by aleriaza          #+#    #+#             */
/*   Updated: 2026/02/16 13:29:10 by dprudnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

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

static void	wait_children(int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		wait(NULL);
		i++;
	}
}

int	execute_multi_cmds(t_pipeline *p, t_shell *shell)
{
	t_exec	exec;

	exec.p = p;
	exec.shell = shell;
	exec.i = 0;
	exec.prev_fd = -1;
	while (exec.i < p->cmd_count)
	{
		if (exec.i < p->cmd_count - 1)
			pipe(exec.pipefd);
		if (fork() == 0)
			exec_child(&exec);
		exec.prev_fd = handle_parent(&exec);
		exec.i++;
	}
	wait_children(p->cmd_count);
	return (0);
}
