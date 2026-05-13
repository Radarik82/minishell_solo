/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_entry.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprudnik <dprudnik@student.42wolfsburg.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 14:11:10 by dprudnik          #+#    #+#             */
/*   Updated: 2026/05/12 14:13:02 by dprudnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *arg)
{
	int	len;

	len = ft_strlen(arg);
	if (ft_strncmp(arg, "echo", len) == 0 ||
		ft_strncmp(arg, "cd", len) == 0 ||
		ft_strncmp(arg, "pwd", len) == 0 ||
		ft_strncmp(arg, "export", len) == 0 ||
		ft_strncmp(arg, "unset", len) == 0 ||
		ft_strncmp(arg, "env", len) == 0 ||
		ft_strncmp(arg, "exit", len) == 0)
		return (1);
	return	(0);
}
