/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_entry.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprudnik <dprudnik@student.42wolfsburg.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 14:11:10 by dprudnik          #+#    #+#             */
/*   Updated: 2026/05/12 14:13:02 by dprudnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     save_std_fds(int *saved_stdin, int *saved_stdout)
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

void    restore_std_fds(int saved_stdin, int saved_stdout)
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

int	is_builtin(char *arg)
{
	int	len;

	len = ft_strlen(arg);
	if (ft_strncmp(arg, "echo", len) == 0 ||
		ft_strncmp(arg, "cd", len) == 0 ||
		ft_strncmp(arg, "pwd", len) == 0 ||
		ft_strncmp(arg, "export", len) == 0 ||
		ft_strncmp(arg, "unset", len) == 0 ||
		ft_strncmp(arg, "env", len) == 0 ||
		ft_strncmp(arg, "exit", len) == 0)
		return (1);
	return	(0);
}
