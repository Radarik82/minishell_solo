/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprudnik <dprudnik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 17:23:08 by aleriaza          #+#    #+#             */
/*   Updated: 2026/05/22 15:31:24 by dprudnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Check if command starts with / */
int	is_absolute_path(char *str)
{
	if (str[0] == '/')
		return (1);
	return (0);
}

/* Check if command starts with ./ or ../ */
int	is_relative_path(char *str)
{
	if (str[0] == '.')
	{
		if (str[1] == '/')
			return (1);
		if (str[1] == '.' && str[2] == '/')
			return (1);
	}
	return (0);
}

/* Build envp from vars, exec the command; child exits on any failure */
void	execute_child(char **args, t_var *vars)
{
	char	**envp;
	char	*cmd_path;
	char	*err;

	signals_set_child_exec();
	envp = vars_to_envp(vars);
	if (is_absolute_path(args[0]) || is_relative_path(args[0]))
		cmd_path = args[0];
	else
		cmd_path = find_command(args[0], vars);
	if (!cmd_path)
	{
		err = ft_strjoin(args[0], ": command not found");
		print_error(err);
		free(err);
		exit(127);
	}
	execve(cmd_path, args, envp);
	perror("execve");
	exit(126);
}

int	fork_and_exec(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		if (cmd->redirs != NULL)
			apply_redirections(cmd->redirs);
		execute_child(cmd->args, shell->vars);
	}
	signals_set_parent_waiting();
	waitpid(pid, &status, 0);
	signals_set_interactive();
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			printf("Quit (core dumped)\n");
		else if (WTERMSIG(status) == SIGINT)
			printf("\n");
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	execute_command(t_cmd *cmd, t_shell *shell)
{
	int	exit_code;

	if (!cmd->args || !cmd->args[0])
		return (0);
	exit_code = fork_and_exec(cmd, shell);
	shell->exit_status = exit_code;
	return (exit_code);
}
