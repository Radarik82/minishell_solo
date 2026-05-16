/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleriaza <aleriaza@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 22:29:00 by denis             #+#    #+#             */
/*   Updated: 2026/05/16 12:11:55 by aleriaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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
		return (cd_not_exist_error(path));
	return (0);
}
int	cd_not_exist_error(char *path)
{
	write(2, "minishell: cd: ", 15);
	write(2, path, ft_strlen(path));
	write(2, ": No such file or directory\n", 28);
	return (1);
}