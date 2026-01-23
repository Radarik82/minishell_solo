/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprudnik <dprudnik@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 16:33:54 by aleriaza          #+#    #+#             */
/*   Updated: 2026/01/23 15:14:52 by dprudnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
