/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmds_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprudnik <dprudnik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 22:25:59 by dprudnik          #+#    #+#             */
/*   Updated: 2026/02/19 17:56:43 by dprudnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	sort_and_printout(t_shell *shell)
{
	char	*value;
	char	*key;
	size_t	vars;
	size_t	i;

	i = 0;
	vars = env_size(shell->env);
	while (i < vars)
	{
		
	}
	if (value)
		ft_printf("declare -x %s=\"%s\"\n", key, value);
	ft_printf("declare -x %s\n", key);

	return (0);
}


int		exec_export(t_cmd *cmd, t_shell *shell)
{
	int	status;

	status = add_env_var(shell->env, cmd->args[1]);//temp!

	if (!cmd->args[1])
		sort_and_printout(shell);



	return (status);
}
