/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariazano <ariazano@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 12:08:54 by ariazano          #+#    #+#             */
/*   Updated: 2023/10/08 00:05:31 by ariazano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_print_x(unsigned int num, unsigned int base, t_arg *param)
{
	int	numlen;
	int	nulls;

	nulls = 0;
	numlen = ft_numlen_prn(num, base);
	if (num == 0)
		param->hash = 0;
	if (num == 0 && param->precision == 0)
	{
		numlen--;
		param->nul = 1;
	}
	if ((param->precision >= 0) && (param->flag == '0'))
		param->flag = 0;
	if (param->precision > numlen)
	{
		nulls = param->precision - numlen;
		numlen = param->precision;
	}
	if (param->hash == 1)
		numlen = numlen + 2;
	ft_p_x_2(num, numlen, nulls, param);
}

void	ft_p_x_2(unsigned int num, int numlen, int nulls, t_arg *param)
{
	if (param->flag == '-')
	{
		if (param->hash == 1)
			ft_putprefix(param);
		ft_p_p(num, nulls, 16, param);
		ft_put_width(numlen, param);
	}
	else if (param->flag == '0')
	{
		if (param->hash == 1)
			ft_putprefix(param);
		ft_put_width(numlen, param);
		ft_p_p(num, nulls, 16, param);
	}
	else
	{
		ft_put_width(numlen, param);
		if (param->hash == 1)
			ft_putprefix(param);
		ft_p_p(num, nulls, 16, param);
	}
}
