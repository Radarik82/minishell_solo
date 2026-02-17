/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprudnik <dprudnik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 16:33:54 by aleriaza          #+#    #+#             */
/*   Updated: 2026/02/17 18:01:39 by dprudnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_and_error(t_pipeline *pipeline, t_shell *shell, char *msg, int code)
{
	free_pipeline(pipeline);
	if (shell)
	{
		if (shell->env)
			free_env(shell->env);
	}
	exit_error(msg, code);
}

void	print_error(char *msg)
{
	if (msg)
	{
		write(2, "minishell: ", 11);
		write(2, msg, ft_strlen(msg));
		write(2, "\n", 1);
	}
}

void	exit_error(char *msg, int code)
{
	print_error(msg);
	exit(code);
}
