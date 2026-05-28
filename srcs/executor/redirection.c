/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleriaza <aleriaza@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 14:33:48 by dprudnik          #+#    #+#             */
/*   Updated: 2026/05/28 13:09:59 by aleriaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_input_redirection(char *infile)
{
	int	infile_fd;

	infile_fd = open(infile, O_RDONLY);
	if (infile_fd == -1)
	{
		perror("open infile");
		return (-1);
	}
	if (dup2(infile_fd, STDIN_FILENO) == -1)
	{
		perror("dup2 input");
		close(infile_fd);
		return (-1);
	}
	close(infile_fd);
	return (0);
}

static int	handle_output_redirection(const char *outfile)
{
	int	outfile_fd;

	outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd == -1)
	{
		perror("open outfile");
		return (-1);
	}
	if (dup2(outfile_fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 output");
		close(outfile_fd);
		return (-1);
	}
	close(outfile_fd);
	return (0);
}

static int	handle_append_redirection(const char *outfile)
{
	int	outfile_fd;

	outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outfile_fd == -1)
	{
		perror("open outfile");
		return (-1);
	}
	if (dup2(outfile_fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 output");
		close(outfile_fd);
		return (-1);
	}
	close(outfile_fd);
	return (0);
}

void	apply_redirections(t_redir *redir)
{
	while (redir)
	{
		if (redir->type == REDIR_IN)
			handle_input_redirection(redir->file);
		else if (redir->type == REDIR_OUT)
			handle_output_redirection(redir->file);
		else if (redir->type == REDIR_APPEND)
			handle_append_redirection(redir->file);
		else if (redir->type == REDIR_HEREDOC)
		{
			handle_input_redirection(redir->file);
			unlink(redir->file);
		}
		redir = redir->next;
	}
}
