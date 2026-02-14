/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprudnik <dprudnik@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 12:10:44 by dprudnik          #+#    #+#             */
/*   Updated: 2026/02/14 22:39:57 by dprudnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_echo(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (args[i] && is_valid_n_flag(args[i]))
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}

int is_valid_n_flag(char *arg)
{
	int	j;

	j = 0;
	if (arg[j] != '-')
		return (0);
	j++;
	if (arg[j] == '\0')
		return (0);
	while (arg[j])
	{
		if (arg[j] != 'n')
			return (0);
		j++;
	}
	return (1);
}


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

int	exec_exit(t_pipeline *p, t_cmd *cmd, t_shell *shell)
{
	write(1, "exit\n", 5);
	if (cmd->args[1])
	{
		print_error("exit: too many arguments");
		return (1);
	}
	else
	{
		free_pipeline(p);
		if (shell)
		{
			if (shell->env)
				free_env(shell->env);
			free(shell);
		}
	}
	exit(0) ;
}

int	exec_env(t_shell *shell)
{
	int	i = 0;

	while (shell->env[i])
	{
		ft_printf("%s\n", shell->env[i]);
		i++;
	}
	return (0);
}
