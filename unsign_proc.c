/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsign_proc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralverta <ralverta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 15:24:25 by ralverta          #+#    #+#             */
/*   Updated: 2021/01/28 14:21:19 by ralverta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	actual_size(t_format *value, unsigned int d, char *str_unsign)
{
	int i;

	i = 0;
	if (value->precision == 0 && d == 0)
		return (0);
	if (value->precision > (int)ft_strlen(str_unsign))
	{
		while (i < value->precision)
			i++;
	}
	else
	{
		while (i < (int)ft_strlen(str_unsign))
			i++;
	}
	return (i);
}

static void	print_precision(t_format *value, char *str_unsign, unsigned int d)
{
	int i;

	i = -1;
	if (value->precision > (int)ft_strlen(str_unsign))
	{
		while (++i < value->precision - (int)ft_strlen(str_unsign))
			write(1, "0", 1);
		ft_putstr_fd(str_unsign, 1);
	}
	else
	{
		if (!(value->precision == 0 && d == 0))
			ft_putstr_fd(str_unsign, 1);
	}
}

static int	flag_zero_proc(t_format *value, char *str_unsign, unsigned int d)
{
	int i;

	i = -1;
	if (value->width > actual_size(value, d, str_unsign))
	{
		while (++i < value->width - actual_size(value, d, str_unsign))
			write(1, "0", 1);
		print_precision(value, str_unsign, d);
		return (value->width);
	}
	else
		print_precision(value, str_unsign, d);
	return (actual_size(value, d, str_unsign));
}

static int	width_proc(t_format *value, char *str_unsign, unsigned int d)
{
	int	i;

	i = -1;
	if (value->width <= actual_size(value, d, str_unsign))
	{
		print_precision(value, str_unsign, d);
		return (actual_size(value, d, str_unsign));
	}
	if (value->flag_minus == 1)
	{
		print_precision(value, str_unsign, d);
		while (++i < value->width - actual_size(value, d, str_unsign))
			write(1, " ", 1);
	}
	else
	{
		while (++i < value->width - actual_size(value, d, str_unsign))
			write(1, " ", 1);
		print_precision(value, str_unsign, d);
	}
	return (value->width);
}

int			unsign_proc(t_format *value, va_list *ap)
{
	unsigned int	d;
	char			*str_unsign;
	int				ret;

	d = va_arg(*ap, unsigned int);
	str_unsign = ft_u_itoa(d);
	if (value->flag_zero == 1 && value->flag_minus != 1 && value->precision < 0)
		ret = flag_zero_proc(value, str_unsign, d);
	else
		ret = width_proc(value, str_unsign, d);
	free(str_unsign);
	return (ret);
}
