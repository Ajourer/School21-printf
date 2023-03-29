/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_proc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralverta <ralverta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 17:51:19 by ralverta          #+#    #+#             */
/*   Updated: 2021/01/28 16:32:03 by ralverta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	actual_size(t_format *value, unsigned int d, char *str_hex)
{
	int i;

	i = 0;
	if (value->precision == 0 && d == 0)
		return (0);
	if (value->precision > (int)ft_strlen(str_hex))
	{
		while (i < value->precision)
			i++;
	}
	else
	{
		while (i < (int)ft_strlen(str_hex))
			i++;
	}
	return (i);
}

static void	print_precision(t_format *value, char *str_hex, unsigned int d)
{
	int i;

	i = -1;
	if (value->precision > (int)ft_strlen(str_hex))
	{
		while (++i < value->precision - (int)ft_strlen(str_hex))
			write(1, "0", 1);
		if (value->type == 'x')
			ft_putstr_fd(str_hex, 1);
		if (value->type == 'X')
			ft_putstr_fd(str_upper(str_hex), 1);
	}
	else
	{
		if (!(value->precision == 0 && d == 0))
		{
			if (value->type == 'x')
				ft_putstr_fd(str_hex, 1);
			if (value->type == 'X')
				ft_putstr_fd(str_upper(str_hex), 1);
		}
	}
}

static int	flag_zero_proc(t_format *value, char *str_hex, unsigned int d)
{
	int i;

	i = -1;
	if (value->width > actual_size(value, d, str_hex))
	{
		while (++i < value->width - actual_size(value, d, str_hex))
			write(1, "0", 1);
		print_precision(value, str_hex, d);
		return (value->width);
	}
	else
		print_precision(value, str_hex, d);
	return (actual_size(value, d, str_hex));
}

static int	width_proc(t_format *value, char *str_hex, unsigned int d)
{
	int	i;

	i = -1;
	if (value->width <= actual_size(value, d, str_hex))
	{
		print_precision(value, str_hex, d);
		return (actual_size(value, d, str_hex));
	}
	if (value->flag_minus == 1)
	{
		print_precision(value, str_hex, d);
		while (++i < value->width - actual_size(value, d, str_hex))
			write(1, " ", 1);
	}
	else
	{
		while (++i < value->width - actual_size(value, d, str_hex))
			write(1, " ", 1);
		print_precision(value, str_hex, d);
	}
	return (value->width);
}

int			hex_proc(t_format *value, va_list *ap)
{
	unsigned int	d;
	char			*str_hex;
	int				ret;

	d = va_arg(*ap, unsigned int);
	str_hex = ft_itoa_base(d);
	if (value->flag_zero == 1 && value->flag_minus != 1 && value->precision < 0)
		ret = flag_zero_proc(value, str_hex, d);
	else
		ret = width_proc(value, str_hex, d);
	free(str_hex);
	return (ret);
}
