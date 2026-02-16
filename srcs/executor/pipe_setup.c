/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprudnik <dprudnik@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 20:32:11 by dprudnik          #+#    #+#             */
/*   Updated: 2026/02/16 13:27:15 by dprudnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	pipeline_readout(t_pipeline *pipeline)//DEBUG ONLY!!!
{
	int	i;

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
			printf(RED"| "RESET);
		i++;
	}
	printf("\n");
}

