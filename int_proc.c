/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_proc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralverta <ralverta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 15:10:43 by ralverta          #+#    #+#             */
/*   Updated: 2021/01/28 16:26:13 by ralverta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	actual_size(t_format *value, int d, char *str_int)
{
	int i;

	i = 0;
	if (value->precision == 0 && d == 0)
		return (0);
	if (value->precision > (int)ft_strlen(str_int))
	{
		while (i < value->precision)
			i++;
	}
	else
	{
		while (i < (int)ft_strlen(str_int))
			i++;
	}
	if (d < 0)
		i++;
	return (i);
}

static void	print_precision(t_format *value, char *str_int, int d)
{
	int i;

	i = -1;
	if (d < 0 && !value->flag_zero)
		write(1, "-", 1);
	if (value->precision > (int)ft_strlen(str_int))
	{
		while (++i < value->precision - (int)ft_strlen(str_int))
			write(1, "0", 1);
		ft_putstr_fd(str_int, 1);
	}
	else
	{
		if (!(value->precision == 0 && d == 0))
			ft_putstr_fd(str_int, 1);
	}
}

static int	flag_zero_proc(t_format *value, char *str_int, int d)
{
	int i;

	i = -1;
	if (d < 0)
		write(1, "-", 1);
	if (value->width > actual_size(value, d, str_int))
	{
		while (++i < value->width - actual_size(value, d, str_int))
			write(1, "0", 1);
		print_precision(value, str_int, d);
		return (value->width);
	}
	else
		print_precision(value, str_int, d);
	return (actual_size(value, d, str_int));
}

static int	width_proc(t_format *value, char *str_int, int d)
{
	int	i;

	i = -1;
	if (value->width <= actual_size(value, d, str_int))
	{
		print_precision(value, str_int, d);
		return (actual_size(value, d, str_int));
	}
	if (value->flag_minus == 1)
	{
		print_precision(value, str_int, d);
		while (++i < value->width - actual_size(value, d, str_int))
			write(1, " ", 1);
	}
	else
	{
		while (++i < value->width - actual_size(value, d, str_int))
			write(1, " ", 1);
		print_precision(value, str_int, d);
	}
	return (value->width);
}

int			int_proc(t_format *value, va_list *ap)
{
	int		d;
	char	*str_int;
	int		ret;

	d = va_arg(*ap, int);
	if (d == INT_MIN)
		str_int = ft_strdup("2147483648");
	else
		str_int = ft_itoa(abs_(d));
	if (value->flag_zero == 1 && value->flag_minus != 1 && value->precision < 0)
		ret = flag_zero_proc(value, str_int, d);
	else
		ret = width_proc(value, str_int, d);
	free(str_int);
	return (ret);
}
