/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariazano <ariazano@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 22:22:53 by ariazano          #+#    #+#             */
/*   Updated: 2023/10/08 00:05:35 by ariazano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_struct_init(t_arg *param)
{
	param->flag = 0;
	param->width = 0;
	param->precision = -1;
	param->type = 0;
	param->minus = 0;
	param->nul = 0;
	param->hash = 0;
	param->plus = 0;
	param->space = 0;
	param->dash = 0;
}

int	ft_printf(const char *str, ...)
{
	t_arg	param;
	va_list	args;

	if (!str)
		return (-1);
	param.len = 0;
	param.fail = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%' && *(++str))
		{
			ft_parser(&str, &param);
			ft_processor(&param, &args);
		}
		else
			ft_putchar_prn(*str, &param);
		str++;
	}
	va_end(args);
	if (param.fail == -1)
		return (param.fail);
	return (param.len);
}

void	ft_parser_part1(const char **str, t_arg *param)
{
	char	minus;

	minus = 0;
	ft_struct_init(param);
	while ((**str == '-' || **str == '0' || **str == ' '
			|| **str == '#' || **str == '+'))
	{
		if (**str == '-')
			minus = '-';
		if (**str == '0')
			param->flag = '0';
		if (**str == ' ')
			param->space = 1;
		if (**str == '#')
			param->hash = 1;
		if (**str == '+')
			param->plus = 1;
		(*str)++;
	}
	if (minus == '-')
		param->flag = '-';
	param->width = ft_atoi_move(str);
}

void	ft_parser(const char **str, t_arg *param)
{
	ft_parser_part1(str, param);
	if (**str == '.')
	{
		(*str)++;
		param->precision = ft_atoi_move(str);
	}
	if (**str == 'd' || **str == 's' || **str == 'c' || **str == 'p' || **str
		== 'x' || **str == 'X' || **str == 'i' || **str == 'u' || **str == '%')
		param->type = **str;
	if (**str == '\0')
		param->len = -1;
}
