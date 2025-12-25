/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_d_i_u.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariazano <ariazano@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 12:08:54 by ariazano          #+#    #+#             */
/*   Updated: 2023/12/05 22:11:20 by ariazano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_put_minus(t_arg *param)
{
	if (param->type == 'd' || param->type == 'i')
	{
		if (param->minus == 1)
			ft_putchar_prn('-', param);
		if (param->plus == 1 && param->minus == 0)
			ft_putchar_prn('+', param);
		if (param->plus == 0 && param->space == 1 && param->minus == 0)
			ft_putchar_prn(' ', param);
	}
}

void	ft_put_width(int numlen, t_arg *param)
{
	while (param->width > numlen)
	{
		if (param->type == 'c' && param->flag == '0')
			param->flag = 0;
		if (param->flag == '0')
			ft_putchar_prn('0', param);
		else
			ft_putchar_prn(' ', param);
		numlen++;
	}
}

void	ft_p_p(unsigned int num, int nulls, int base, t_arg *param)
{
	while (nulls--)
		ft_putchar_prn('0', param);
	ft_putnbr_prn(num, base, param);
}

void	ft_print_d(unsigned int num, unsigned int base, t_arg *param)
{
	int	numlen;
	int	nulls;

	nulls = 0;
	numlen = ft_numlen_prn(num, base);
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
	if ((param->minus == 1) || (param->plus == 1 && param->minus == 0)
		|| (param->plus == 0 && param->space == 1 && param->minus == 0))
		numlen++;
	ft_p_d_2(num, numlen, nulls, param);
}

void	ft_p_d_2(unsigned int num, int numlen, int nulls, t_arg *param)
{
	int	base;

	base = 10;
	if (param->flag == '-')
	{
		ft_put_minus(param);
		ft_p_p(num, nulls, base, param);
		ft_put_width(numlen, param);
	}
	else if (param->flag == '0')
	{
		ft_put_minus(param);
		ft_put_width(numlen, param);
		ft_p_p(num, nulls, base, param);
	}
	else
	{
		ft_put_width(numlen, param);
		ft_put_minus(param);
		ft_p_p(num, nulls, base, param);
	}
}
