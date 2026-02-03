/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprudnik <dprudnik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 16:43:43 by aleriaza          #+#    #+#             */
/*   Updated: 2026/02/03 13:08:49 by dprudnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	command_readout(t_pipeline *pipeline, t_shell *shell)//DEBUG ONLY!!!
{
	int	i = 0;

	while (shell->env[i])
	{
		printf("%s\n", shell->env[i]);
		i++;
	}
	i = 0;
	while (pipeline->cmds[i])
	{
		int	j = 0;
		while (pipeline->cmds[i]->args[j])
		{
			printf("* ");
			printf("%s ", pipeline->cmds[i]->args[j]);
			printf("* ");
			j++;
		}
		if (pipeline->cmds[i + 1])
			printf(RED"Need PIPE! "RESET);
		i++;
	}
	printf("\n");
}


void	run_pipeline(t_pipeline *pipeline, t_shell *shell)
{
	int	i = 0;

	while (shell->env[i])
	{
		printf("%s\n", shell->env[i]);
		i++;
	}
	i = 0;
	while (pipeline->cmds[i])
	{
		int	j = 0;
		while (pipeline->cmds[i]->args[j])
		{
			printf("*");
			printf("%s", pipeline->cmds[i]->args[j]);
			printf("*");
			j++;
		}
		if (pipeline->cmds[i + 1])
			printf(RED" | "RESET);
		i++;
	}
	printf("\n");
	return;
}
