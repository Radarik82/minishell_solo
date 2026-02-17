/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprudnik <dprudnik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 16:06:23 by aleriaza          #+#    #+#             */
/*   Updated: 2026/02/17 17:55:04 by dprudnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_received = 0;

/* Free shell and exit */
static void	cleanup_shell(t_shell *shell)
{
	if (shell)
	{
		if (shell->env)
			free_env(shell->env);
	}
}

static void	init_shell(t_shell *shell, char **envp)
{
	shell->env = copy_env(envp);
	if (!shell->env)
		exit_error("env copy failed", 1);
	shell->exit_status = 0;
}

static void	process_line(char *line, t_shell *shell)
{
	char		**segments;
	t_pipeline	*pipeline;

	if (!line || line[0] == '\0')
		return ;
	add_history(line);
	segments = split_by_pipes(line);
	if (!segments)
		return ;
	pipeline = create_pipeline(segments);
	free_array(segments);
	if (!pipeline)
		return ;
	run_pipeline(pipeline, shell);// Execution point.
	free_pipeline(pipeline);
}

static void	shell_loop(t_shell *shell)
{
	char	*line;

	while (1)
	{
		setup_signals();
		line = readline(GREEN"minishell> "RESET);
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		process_line(line, shell);
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	shell_loop(&shell);
	cleanup_shell(&shell);
	return (shell.exit_status);
}
