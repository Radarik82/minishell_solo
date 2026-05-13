/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprudnik <dprudnik@student.42wolfsburg.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:32:39 by dprudnik          #+#    #+#             */
/*   Updated: 2026/05/12 17:06:00 by dprudnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// TODO : need function for cd.
// TODO : Do I need to handle all chdir() errors???
// FIX : need to change.
int	exec_cd(t_cmd *cmd, t_shell *shell)
{
	(void)cmd;//tmp
	(void)shell;//tmp
	int	ret;

	if (cmd->args[2])
	{
		print_error("cd: too many arguments");
		shell->exit_status = 1;
	}
	ret = chdir(cmd->args[1]);
	if (ret == -1)
	{
		print_error("cd: No such file or directory");
		return (1);
	}
	return (0);
}

// TODO : may need to change to use getcwd().
int	exec_pwd(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	if (cmd->args[1])
	{
		print_error("pwd: too many arguments");
		shell->exit_status = 2;
		return (2);
	}
	path = get_env_var("PWD", shell->env);
	if (!path)
		print_error("pwd: get_env_var failed!");
	ft_printf("%s\n", path);
	return (0);
}

int	exec_export(t_cmd *cmd, t_shell *shell)
{
	(void)cmd;//tmp
	(void)shell;//tmp

	return (0);
}

int	exec_unset(t_cmd *cmd, t_shell *shell)
{
	(void)cmd;//tmp
	(void)shell;//tmp

	return (0);
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

int	exec_exit(t_cmd *cmd, t_shell *shell)
{
	int	exit_code;

	exit_code = 0;
	if (cmd->args[1])
	{
		print_error("exit: too many arguments");
		exit_code = 2;
	}
	write(1, "exit\n", 5);
	free_cmd_list(cmd);
	if (shell->env)
		free_env(shell->env);
	exit(exit_code);
}
