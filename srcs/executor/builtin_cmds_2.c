/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmds_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprudnik <dprudnik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 22:25:59 by dprudnik          #+#    #+#             */
/*   Updated: 2026/02/19 16:14:14 by dprudnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*get_exit_status(t_shell *shell)
{
	return ft_itoa(shell->exit_status);
}

int	exec_pwd(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	if (cmd->args[1])
	{
		print_error("pwd: too many arguments");
		return (2);
	}
	path = get_env_var("PWD", shell->env);
	if (!path)
		print_error("pwd: get_env_var failed!");
	ft_printf("%s\n", path);
	return (0);
}
