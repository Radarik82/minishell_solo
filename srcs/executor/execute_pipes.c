/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprudnik <dprudnik@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 16:43:43 by aleriaza          #+#    #+#             */
/*   Updated: 2026/01/30 19:50:36 by dprudnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

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
			printf("* ");
			printf("%s ", pipeline->cmds[i]->args[j]);
			printf("* ");
			j++;
		}
		if (pipeline->cmds[i + 1])
			printf("| ");
		i++;
	}
	printf("\n");
	return;
}
