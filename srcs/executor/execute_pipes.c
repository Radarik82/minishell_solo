/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprudnik <dprudnik@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 16:43:43 by aleriaza          #+#    #+#             */
/*   Updated: 2026/01/23 19:02:09 by dprudnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	run_pipeline(t_pipeline *pipeline, t_shell *shell)
{
	printf("%s\n", shell->env[0]);// temp just to see what happens so far
	printf("%d\n", pipeline->cmd_count);//same for this line

	return;
}
