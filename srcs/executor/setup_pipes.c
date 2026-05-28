/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleriaza <aleriaza@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 16:36:06 by aleriaza          #+#    #+#             */
/*   Updated: 2026/05/28 13:12:16 by aleriaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipe_fds(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

void	setup_input_pipe(int fd)
{
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	setup_output_pipe(int *fd)
{
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
}
