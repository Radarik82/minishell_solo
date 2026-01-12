/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleriaza <aleriaza@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 16:36:06 by aleriaza          #+#    #+#             */
/*   Updated: 2026/01/12 16:43:14 by aleriaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

int create_pipe_fds(int *fd)
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	return (0);
}

void close_pipe_fds(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

void setup_input_pipe(int *fd)
{
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
}

void setup_output_pipe(int *fd)
{
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
}

void close_unused_pipes(int *prev_fd, int *curr_fd)
{
	if (prev_fd)
		close_pipe_fds(prev_fd);
	if (curr_fd)
		close_pipe_fds(curr_fd);
}
