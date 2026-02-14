/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_mod_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprudnik <dprudnik@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 18:04:55 by dprudnik          #+#    #+#             */
/*   Updated: 2026/02/13 18:56:17 by dprudnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_env_var(char *key, char *value)
{
	char	*tmp;
	char	*new_var;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	new_var = ft_strjoin(tmp, value);
	free(tmp);
	return (new_var);
}

int	find_env_index(char **env, char *key)
{
	int	i;
	int	len;

	if (!env || !key)
		return (-1);
	len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, len)
			&& env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	add_env_var(char ***env, char *new_var)
{
	char	**new_env;
	int		i;

	i = 0;
	while ((*env)[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (1);
	i = -1;
	while ((*env)[++i])
		new_env[i] = (*env)[i];
	new_env[i] = new_var;
	new_env[i + 1] = NULL;
	free(*env);
	*env = new_env;
	return (0);
}

/*update local env list*/
int	update_env(char ***env, char *key, char *value)
{
	int		index;
	char	*new_var;

	if (!env || !*env || !key || !value)
		return (-1);
	new_var = create_env_var(key, value);
	if (!new_var)
		return (1);
	index = find_env_index(*env, key);
	if (index != -1)
	{
		free((*env)[index]);
		(*env)[index] = new_var;
		return (0);
	}
	return (add_env_var(env, new_var));
}
