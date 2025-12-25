/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_prn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariazano <ariazano@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 12:08:54 by ariazano          #+#    #+#             */
/*   Updated: 2023/12/05 22:11:49 by ariazano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_prn(char c, t_arg *param)
{
	if (param->fail == -1)
		return ;
	if (write(1, &c, 1) == -1)
		param->fail = -1;
	param->len++;
}

int	ft_atoi_move(const char **str)
{
	int	num;

	num = 0;
	if (**str == '\0')
		return (0);
	while (**str >= '0' && **str <= '9')
	{
		num = num * 10 + (**str - '0');
		(*str)++;
	}
	return (num);
}

int	ft_numlen_prn(unsigned num, unsigned base)
{
	int	len;

	if (num == 0)
		return (1);
	len = 0;
	while (num > 0)
	{
		num = num / base;
		len++;
	}
	return (len);
}

void	ft_putnbr_prn(unsigned num, unsigned base, t_arg *param)
{
	int	a;
	int	toupper;

	if (param->nul == 1)
		return ;
	toupper = 0;
	if (param->type == 'X')
		toupper = 32;
	if (num < base)
	{
		if (num < 10)
			a = num + 48;
		else
			a = num - 10 + 'a' - toupper;
		ft_putchar_prn(a, param);
	}
	if (num >= base)
	{
		ft_putnbr_prn(num / base, base, param);
		ft_putnbr_prn(num % base, base, param);
	}
}

void	ft_putstr_prn(char *str, int strlen, t_arg *param)
{
	if (str)
	{
		while (strlen && *str)
		{
			ft_putchar_prn(*str++, param);
			strlen--;
		}
	}
}
