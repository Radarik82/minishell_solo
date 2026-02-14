/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprudnik <dprudnik@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 16:43:43 by aleriaza          #+#    #+#             */
/*   Updated: 2026/02/14 22:32:46 by dprudnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	run_pipeline(t_pipeline *pipeline, t_shell *shell)
{
	// int	**fds;

	if (pipeline->cmd_count == 1 && is_builtin(pipeline->cmds[0]->args[0]))
	{
		execute_builtin(pipeline, pipeline->cmds[0], shell);
		return ;
	}
	if (pipeline->cmd_count == 1)// Temporary Only for single extern arg with no redirections
	{
		execute_command(pipeline->cmds[0]->args, shell);
		return ;
	}
	// if (setup_pipes(&fds, pipeline) == -1)
	// 	free_and_error(pipeline, shell, "Pipes error", 1);
	// command_readout(pipeline, shell);//Debug Only
}

// int	setup_pipes(int ***fds, t_pipeline *pipeline)
// {

// 	*fds = malloc(sizeof(*fds) * pipeline->cmd_count - 1);
// 	if (!*fds)
// 		return (-1);
// }

// void exec_cmd(t_pipeline *pipeline, t_cmd *cmd, t_fds *fds, t_shell *shell)
// {
// 	pid_t pid = fork();

// 	if (pid == -1)
// 		free_and_error(pipeline, shell, "Fork Error", 1);
// 	if (pid == 0) // Child process
// 	{
// 		if (cmd->infile)
// 		{
// 			if (handle_input_redirection(cmd->infile) == -1)
// 				free_and_error(pipeline, shell, "Redir Error", 2);
// 		}
// 		if (cmd->outfile)
// 		{
// 			if (handle_output_redirection(cmd->outfile, cmd->append) == -1)
// 				free_and_error(pipeline, shell, "Redir Error", 3);
// 		}
// 		if (fds->input_fd)
// 		{
// 			dup2(fds->input_fd[0], STDIN_FILENO);  // Set stdin to the read end of the previous pipe
// 			close(fds->input_fd[0]);
// 		}
// 		if (fds->output_fd)
// 		{
// 			dup2(fds->output_fd[1], STDOUT_FILENO);  // Set stdout to the write end of the current pipe
// 			close(fds->output_fd[1]);
// 		}
// 		char *cmd_path = cmd->args[0]; // Use the command name (e.g., "cat", "grep", etc.)
// 		if (execve(cmd_path, cmd->args, shell->env) == -1)
// 			free_and_error(pipeline, shell, "Execve Error", 4);
// 	}
// }

// void run_pipeline_recursive(t_pipeline *pipeline, t_shell *shell, int current_index, int *input_fd)
// {
// 	t_cmd	*cmd;
// 	t_fds	fds;
// 	int		pipe_fds[2];

// 	if (current_index >= pipeline->cmd_count)
// 		return;
// 	fds.input_fd = input_fd;
// 	cmd = pipeline->cmds[current_index];
// 	if (current_index < pipeline->cmd_count - 1)
// 	{
// 		if (pipe(pipe_fds) == -1)
// 			return;
// 		fds.output_fd = pipe_fds;
// 	}
// 	exec_cmd(pipeline, cmd, &fds, shell);
// 	if (fds.output_fd)
// 	{
// 		close(pipe_fds[1]);
// 		run_pipeline_recursive(pipeline, shell, current_index + 1, pipe_fds);
// 	}
// 	else
// 		run_pipeline_recursive(pipeline, shell, current_index + 1, NULL);
// 	wait(NULL);
// }

void	command_readout(t_pipeline *pipeline)//DEBUG ONLY!!!
{
	int	i;

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
