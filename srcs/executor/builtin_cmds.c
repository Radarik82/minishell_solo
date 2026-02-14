/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprudnik <dprudnik@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 12:10:44 by dprudnik          #+#    #+#             */
/*   Updated: 2026/02/14 16:37:08 by dprudnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	exec_cd(char *path)//TODO: illigal to use setenv!!
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
	return (0);
}

void	exec_exit(t_pipeline *pipeline, t_shell *shell)
{
	write(1, "exit\n", 5);
	if (pipeline->cmds[0]->args[1])
	{
		print_error("exit: too many arguments");
		return ;
	}
	else
	{
		free_pipeline(pipeline);
		if (shell)
		{
			if (shell->env)
				free_env(shell->env);
			free(shell);
		}
	}
	exit(0) ;
}
