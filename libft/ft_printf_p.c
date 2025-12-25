/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariazano <ariazano@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 14:07:57 by ariazano          #+#    #+#             */
/*   Updated: 2023/12/05 22:11:26 by ariazano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ptrlen(unsigned long long int num)
{
	int	len;

	if (num == 0)
		return (3);
	len = 0;
	while (num > 0)
	{
		num = num / 16;
		len++;
	}
	return (len + 2);
}

void	ft_putnbr_hex(unsigned long long int n, t_arg *param)
{
	int	a;

	if (param->nul == 1)
		return ;
	if (n < 16)
	{
		if (n < 10)
			a = n + 48;
		else
			a = n - 10 + 'a';
		ft_putchar_prn(a, param);
	}
	if (n >= 16)
	{
		ft_putnbr_hex(n / 16, param);
		ft_putnbr_hex(n % 16, param);
	}
}

void	ft_putprefix(t_arg *param)
{
	if (param->type == 'X')
		ft_putstr_prn("0X", 2, param);
	else
		ft_putstr_prn("0x", 2, param);
}

void	ft_print_p(void *n, t_arg *param)
{
	int					numlen;
	unsigned long int	num;

	if (n == NULL)
		num = 0;
	num = (unsigned long int )n;
	numlen = ft_ptrlen(num);
	if (param->precision == 0 && n == NULL)
	{
		param->nul = 1;
		numlen = 2;
	}
	ft_print_p_part2(num, param, numlen);
}

void	ft_print_p_part2(unsigned long int num, t_arg *param, int numlen)
{
	if (param->flag == '-')
	{
		ft_putprefix(param);
		ft_putnbr_hex(num, param);
		ft_put_width(numlen, param);
	}
	else if (param->flag == '0')
	{
		ft_putprefix(param);
		ft_put_width(numlen, param);
		ft_putnbr_hex(num, param);
	}
	else
	{
		ft_put_width(numlen, param);
		ft_putprefix(param);
		ft_putnbr_hex(num, param);
	}
}
