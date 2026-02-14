/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprudnik <dprudnik@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 12:10:44 by dprudnik          #+#    #+#             */
/*   Updated: 2026/02/14 11:06:59 by dprudnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	cd_cmd(const char *path)
{
	char	cwd[1024];

	if (path == NULL || ft_strncmp(path, "~", ft_strlen(path)) == 0)
		path = getenv("HOME");

	if (chdir(path) == -1)
	{
		perror("cd");
	} else
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			setenv("PWD", cwd, 1);
	}
}

void	exit_cmd(t_pipeline *pipeline)
{
	free_pipeline(pipeline);
	exit(0) ;
}

int	execute_builtin(t_pipeline *pipeline, t_shell *shell)
{
	if (pipeline->cmds[0]->infile)


}
int	execute_builtin_with_redirection(t_cmd *cmd)
{
	int	saved_stdin;
	int	saved_stdout;

	if (save_std_fds(&saved_stdin, &saved_stdout) == -1)
		return (1);

	if (apply_redirections(cmd) == -1)
	{
		restore_std_fds(saved_stdin, saved_stdout);
		return (1);
	}

	exec_builtin(cmd);

	restore_std_fds(saved_stdin, saved_stdout);
	return (0);
}

