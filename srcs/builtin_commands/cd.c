/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denis <dprudnik@student.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 22:29:00 by denis             #+#    #+#             */
/*   Updated: 2026/05/13 22:29:12 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

// TODO : Do I need to handle all chdir() errors???
// TODO : Need to updated OLDPWD in env after every cd
// and need to handle if get_env_var("OLDPWD", retuns NULL.
// BUG : Need to fix! Info in Things to discuss file.
int	exec_cd(t_cmd *cmd, t_shell *shell)
{
	int		ret;
	char	*path;

	if (cmd->args[2])
	{
		print_error("cd: too many arguments");
		shell->exit_status = 1;
		return (1);
	}
	else if (!cmd->args[1])
		path = get_env_var("HOME", shell->env);
	else if (cmd->args[1][0] == '-' && cmd->args[1][1] == '\0')
		path = get_env_var("OLDPWD", shell->env);
	else
		path = cmd->args[1];
	ret = chdir(path);
	if (ret == -1)
	{
		print_error("cd: No such file or directory");
		shell->exit_status = 1;
	}
	return (0);
}
