/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprudnik <dprudnik@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 16:43:43 by aleriaza          #+#    #+#             */
/*   Updated: 2026/02/12 16:38:37 by dprudnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	command_readout(t_pipeline *pipeline, t_shell *shell)//DEBUG ONLY!!!
{
	int	i = 0;

	while (shell->env[i])
	{
		printf("%s\n", shell->env[i]);
		i++;
	}
	i = 0;
	while (pipeline->cmds[i])
	{
		int	j = 0;
		while (pipeline->cmds[i]->args[j])
		{
			printf("* ");
			printf("%s ", pipeline->cmds[i]->args[j]);
			printf("* ");
			j++;
		}
		if (pipeline->cmds[i + 1])
			printf(RED"| "RESET);
		i++;
	}
	printf("\n");
}

void	run_pipeline(t_pipeline *pipeline, t_shell *shell)
{
	// command_readout(pipeline, shell);
	run_pipeline_recursive(pipeline, shell, 0, NULL);
}

int	handle_input_redirection(char *infile)
{
	int	infile_fd;

	infile_fd = open(infile, O_RDONLY);
	if (infile_fd == -1)
	{
		perror("open infile");
		return -1;
	}
	if (dup2(infile_fd, STDIN_FILENO) == -1)
	{
		perror("dup2 input");
		close(infile_fd);
		return -1;
	}
	close(infile_fd);
	return 0;
}

int handle_output_redirection(const char *outfile, int append)
{
	int	flags;
	int	outfile_fd;

	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	outfile_fd = open(outfile, flags, 0644);
	if (outfile_fd == -1)
	{
		perror("open outfile");
		return -1;
	}
	if (dup2(outfile_fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 output");
		close(outfile_fd);
		return -1;
	}
	close(outfile_fd);
	return 0;
}

void exec_cmd(t_pipeline *pipeline, t_cmd *cmd, t_fds *fds, t_shell *shell)
{
	pid_t pid = fork();

	if (pid == -1)
		free_and_error(pipeline, "Fork Error", 1);
	if (pid == 0) // Child process
	{
		if (cmd->infile)
		{
			if (handle_input_redirection(cmd->infile) == -1)
				free_and_error(pipeline, "Redir Error", 2);
		}
		if (cmd->outfile)
		{
			if (handle_output_redirection(cmd->outfile, cmd->append) == -1)
				free_and_error(pipeline, "Redir Error", 3);
		}
		if (fds->input_fd)
		{
			dup2(fds->input_fd[0], STDIN_FILENO);  // Set stdin to the read end of the previous pipe
			close(fds->input_fd[0]);
		}
		if (fds->output_fd)
		{
			dup2(fds->output_fd[1], STDOUT_FILENO);  // Set stdout to the write end of the current pipe
			close(fds->output_fd[1]);
		}
		char *cmd_path = cmd->args[0]; // Use the command name (e.g., "cat", "grep", etc.)
		if (execve(cmd_path, cmd->args, shell->env) == -1)
			free_and_error(pipeline, "Execve Error", 4);
	}
}

void run_pipeline_recursive(t_pipeline *pipeline, t_shell *shell, int current_index, int *input_fd)
{
	t_cmd	*cmd;
	t_fds	fds;
	int		pipe_fds[2];

	if (current_index >= pipeline->cmd_count)
		return; // Base case: All commands executed
	fds.input_fd = input_fd;
	cmd = pipeline->cmds[current_index];// If this is not the last command, create a pipe
	fds.output_fd = NULL;
	if (current_index < pipeline->cmd_count - 1) // Not the last command
	{
		if (pipe(pipe_fds) == -1)
			return;
		fds.output_fd = pipe_fds; // The write end of the current pipe
	}// Execute the current command
	exec_cmd(pipeline, cmd, &fds, shell);
	// If this is not the last command, close the write end of the pipe in the parent
	if (fds.output_fd)
	{
		close(pipe_fds[1]);
		run_pipeline_recursive(pipeline, shell, current_index + 1, pipe_fds);
	}
	else
		run_pipeline_recursive(pipeline, shell, current_index + 1, NULL);
	wait(NULL);
}
