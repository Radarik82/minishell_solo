/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprudnik <dprudnik@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 20:32:11 by dprudnik          #+#    #+#             */
/*   Updated: 2026/02/16 11:57:06 by dprudnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_pipe(t_pipeline *pipline, t_fds *fds, int count)
{
	if (count == 0)//if first command
	{
		if (create_pipe_fds(fds->curr_fds))
			return (-1);
		setup_output_pipe(fds->curr_fds);
	}
	else if ((count + 1) == pipline->cmd_count)// if last command
	{
		setup_input_pipe(fds->prev_fds);
		return (0);
	}
	else//middle pipe
	{
		setup_input_pipe(fds->prev_fds);
		if (create_pipe_fds(fds->curr_fds) == -1)
			return (-1);
		setup_output_pipe(fds->curr_fds);
	}
	fds->prev_fds[0] = fds->curr_fds[0];
	fds->prev_fds[1] = fds->curr_fds[1];
	return (1);
}

pid_t	fork_loop(t_pipeline *pipeline, int *count)
{
	pid_t	pid;
	t_fds	fds;
	int		saved_stdout;

	saved_stdout = stdout;
	while ((*count) < pipeline->cmd_count)
	{
		ft_printf("count:%d", (*count));//debugging
		ft_printf(" of:%d", pipeline->cmd_count);//debugging
		if (setup_pipe(pipeline, &fds, (*count)) == -1)
			return (-1);
		pid = fork();
		if (pid == -1)
			return (-1);
		if (pid == 0)
		{
			close(fds.prev_fds[0]);//closes unused read end in child pipe
			break ;
		}
		(*count)++;
	}
	dup2(saved_stdout, STDOUT_FILENO);
	close_pipe_fds(fds.curr_fds);
	return (pid);
}

int	check_and_exec(char **args, t_shell *shell)
{
	if (!args || !args[0])
		return (-1);
	execute_child(args, shell->env);
	return (1);
}
