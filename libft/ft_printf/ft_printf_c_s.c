/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_c_s.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariazano <ariazano@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 12:08:54 by ariazano          #+#    #+#             */
/*   Updated: 2023/10/08 00:06:29 by ariazano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strlen_prn(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_print_s(char *str, t_arg *param)
{
	int	strlen;

	strlen = ft_strlen_prn(str);
	if (param->precision >= 0 && param->precision < strlen)
	{
		strlen = param->precision;
	}
	if (param->flag == '-')
	{
		ft_putstr_prn(str, strlen, param);
		ft_put_width(strlen, param);
	}
	else
	{
		ft_put_width(strlen, param);
		ft_putstr_prn(str, strlen, param);
	}
}

void	ft_print_c(char c, t_arg *param)
{
	if (param->flag == '-')
	{
		ft_putchar_prn(c, param);
		ft_put_width(1, param);
	}
	else
	{
		ft_put_width(1, param);
		ft_putchar_prn(c, param);
	}
}
