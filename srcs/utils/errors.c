/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleriaza <aleriaza@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 16:33:54 by aleriaza          #+#    #+#             */
/*   Updated: 2025/12/25 16:56:25 by aleriaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
