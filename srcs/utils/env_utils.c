
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleriaza <aleriaza@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 16:30:39 by aleriaza          #+#    #+#             */
/*   Updated: 2025/12/25 16:56:22 by aleriaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Count environment variables */
int	env_size(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

char	**copy_env(char **env)
{
	char	**new_env;
	int		i;
	int		size;

	size = env_size(env);
	new_env = malloc(sizeof(char *) * (size + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			free_env(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

void	free_env(char **env)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

int	set_env_var(char *name, char *value, t_shell *shell)
{
	char	*entry;
	int		len;
	int		i;

	entry = ft_strjoin(name, "=");
	entry = ft_strjoin_free(entry, value);
	if (!entry)
		return (-1);
	len = ft_strlen(name);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, len) == 0
			&& shell->env[i][len] == '=')
		{
			free(shell->env[i]);
			shell->env[i] = entry;
			return (0);
		}
		i++;
	}
	free(entry);
	return (-1);
}

char	*get_env_var(char *name, char **env)
{
	int		i;
	int		len;
	char	*value;

	if (!name || !env)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0)
		{
			if (env[i][len] == '=')
			{
				value = env[i] + len + 1;
				return (value);
			}
		}
		i++;
	}
	return (NULL);
}
