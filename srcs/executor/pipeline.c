/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleriaza <aleriaza@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 00:00:00 by aleriaza          #+#    #+#             */
/*   Updated: 2026/05/22 00:00:00 by aleriaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_pipe(t_exec *ex)
{
	if (!ex->cmd->next)
		return (0);
	if (pipe(ex->pipe.fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	return (0);
}

static void	wait_children(t_pipe *pipe, t_shell *shell)
{
	int		status;
	pid_t	pid;

	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		if (pid == pipe->pid)
		{
			if (WIFEXITED(status))
				shell->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				shell->exit_status = 128 + WTERMSIG(status);
		}
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGQUIT)
				printf("Quit (core dumped)\n");
			else if (WTERMSIG(status) == SIGINT)
				printf("\n");
		}
		pid = waitpid(-1, &status, 0);
	}
}

static void	child_process(t_exec *ex)
{
	ex->shell->in_child = 1;
	signals_set_child_exec();
	if (ex->pipe.in != STDIN_FILENO)
		setup_input_pipe(ex->pipe.in);
	if (ex->cmd->next)
		setup_output_pipe(ex->pipe.fd);
	if (is_builtin(ex->cmd->args[0]))
		exit(execute_builtin(ex->cmd, ex->shell));
	else
	{
		if (ex->cmd->redirs != NULL)
			apply_redirections(ex->cmd->redirs);
		execute_child(ex->cmd->args, ex->shell->vars);
	}
}

static void	parent_process(t_exec *ex)
{
	if (ex->pipe.in != STDIN_FILENO)
		close(ex->pipe.in);
	if (!ex->cmd->next)
		return ;
	close(ex->pipe.fd[1]);
	ex->pipe.in = ex->pipe.fd[0];
}

int	execute_pipeline(t_cmd *cmds, t_shell *shell)
{
	t_exec	ex;

	ex.shell = shell;
	ex.cmd = cmds;
	ex.pipe.in = STDIN_FILENO;
	ex.pipe.cmd_count = cmd_count(cmds);
	signals_set_parent_waiting();
	while (ex.cmd)
	{
		if (open_pipe(&ex))
			return (signals_set_interactive(), 1);
		ex.pipe.pid = fork();
		if (ex.pipe.pid == -1)
			return (perror("fork"), signals_set_interactive(), 1);
		if (ex.pipe.pid == 0)
			child_process(&ex);
		parent_process(&ex);
		ex.cmd = ex.cmd->next;
	}
	wait_children(&ex.pipe, shell);
	signals_set_interactive();
	return (0);
}
