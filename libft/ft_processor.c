/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_processor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariazano <ariazano@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 12:08:54 by ariazano          #+#    #+#             */
/*   Updated: 2023/12/05 22:11:37 by ariazano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_process_d(t_arg *param, va_list *args)
{
	int				num;
	unsigned int	n;

	num = va_arg(*args, int);
	if (num < 0)
	{
		n = -num;
		param->minus = 1;
	}
	else
		n = num;
	ft_print_d(n, 10, param);
}

void	ft_processor(t_arg *param, va_list *args)
{
	char	*str;

	if (param->type == 'd' || param->type == 'i')
		ft_process_d(param, args);
	else if (param->type == 'u')
		ft_print_d(va_arg(*args, unsigned), 10, param);
	else if (param->type == 'x' || param->type == 'X')
		ft_print_x(va_arg(*args, unsigned), 16, param);
	else if (param->type == 'p')
		ft_print_p(va_arg(*args, void *), param);
	else if (param->type == 's')
	{
		str = va_arg(*args, char *);
		if (!(str))
			str = "(null)";
		ft_print_s(str, param);
	}
	else if (param->type == 'c')
		ft_print_c(va_arg(*args, int), param);
	else if (param->type == '%')
		ft_print_c('%', param);
}
