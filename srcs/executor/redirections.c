/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprudnik <dprudnik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 10:53:24 by dprudnik          #+#    #+#             */
/*   Updated: 2026/02/17 12:20:04 by dprudnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	handle_output_redirection(const char *outfile, int append)
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

int	save_std_fds(int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
	if (*saved_stdin == -1 || *saved_stdout == -1)
	{
		perror("dup");
		return (-1);
	}
	return (0);
}

void	restore_std_fds(int saved_stdin, int saved_stdout)
{
	if (saved_stdin != -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
}




/* TEMPORARY not for production!!*/
// int	execute_builtin_with_redirection(t_cmd *cmd)
// {
// 	int	saved_stdin;
// 	int	saved_stdout;

// 	if (save_std_fds(&saved_stdin, &saved_stdout) == -1)
// 		return (1);

// 	if (apply_redirections(cmd) == -1)
// 	{
// 		restore_std_fds(saved_stdin, saved_stdout);
// 		return (1);
// 	}

// 	execute_builtin(cmd);

// 	restore_std_fds(saved_stdin, saved_stdout);
// 	return (0);
// }
