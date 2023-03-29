/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralverta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 18:58:48 by ralverta          #+#    #+#             */
/*   Updated: 2021/01/28 18:30:30 by ralverta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	value_init(t_format *value)
{
	value->type = 0;
	value->width = 0;
	value->precision = -1;
	value->flag_zero = 0;
	value->flag_minus = 0;
}

static void	flag_parse(char *str, t_format *value)
{
	while (str[value->i] == '-' || str[value->i] == '0')
	{
		if (str[value->i] == '-')
			value->flag_minus = 1;
		else if (str[value->i] == '0')
			value->flag_zero = 1;
		value->i++;
	}
}

static void	width_parse(char *str, va_list *ap, t_format *value)
{
	if (ft_isdigit(str[value->i]) == 1)
		value->width = ft_atoi(str + value->i);
	else if (str[value->i] == '*')
	{
		value->width = va_arg(*ap, int);
		if (value->width < 0)
		{
			value->width *= (-1);
			value->flag_minus = 1;
			value->flag_zero = 0;
		}
	}
	while (ft_isdigit(str[value->i]) || str[value->i] == '*')
		value->i++;
}

static void	precision_parse(char *str, va_list *ap, t_format *value)
{
	if (str[value->i] == '.')
	{
		value->precision = 0;
		value->i++;
		if (ft_isdigit(str[value->i]))
			value->precision = ft_atoi(str + value->i);
		else if (str[value->i] == '*')
		{
			value->precision = va_arg(*ap, int);
			if (value->precision < 0)
				value->precision = -1;
		}
		while (ft_isdigit(str[value->i]) || str[value->i] == '*')
			value->i++;
	}
}

void		final_parse(char *str, va_list *ap, t_format *value)
{
	value_init(value);
	flag_parse(str, value);
	if (value->flag_minus)
		value->flag_zero = 0;
	width_parse(str, ap, value);
	precision_parse(str, ap, value);
	value->type = str[value->i];
	if (value->type != 'c' && value->type != '%')
		value->flag_zero = value->precision >= 0 ? 0 : value->flag_zero;
	value->i++;
}
