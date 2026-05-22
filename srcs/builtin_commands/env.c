/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprudnik <dprudnik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 15:58:57 by dprudnik          #+#    #+#             */
/*   Updated: 2026/05/22 16:00:06 by dprudnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Print all exported environment variables as NAME=VALUE */
int	exec_env(t_shell *shell)
{
	t_var	*cur;

	cur = shell->vars;
	while (cur)
	{
		if (cur->exported)
			ft_printf("%s=%s\n", cur->name, cur->value);
		cur = cur->next;
	}
	return (0);
}
