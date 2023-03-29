/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer_proc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralverta <ralverta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 20:42:32 by ralverta          #+#    #+#             */
/*   Updated: 2021/01/28 18:20:05 by ralverta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	actual_size(char *str_pointer, unsigned long d, t_format *value)
{
	int i;

	i = 0;
	if (value->precision == 0 && d == 0)
		return (2);
	while (i < (int)ft_strlen(str_pointer))
		i++;
	i += 2;
	return (i);
}

static void	print_pointer(char *str_pointer, unsigned long d, t_format *value)
{
	write(1, "0", 1);
	write(1, "x", 1);
	if (!(value->precision == 0 && d == 0))
		ft_putstr_fd(str_pointer, 1);
}

static int	width_proc(t_format *value, char *str_pointer, unsigned long d)
{
	int	i;

	i = -1;
	if (value->width <= actual_size(str_pointer, d, value))
	{
		print_pointer(str_pointer, d, value);
		return (actual_size(str_pointer, d, value));
	}
	if (value->flag_minus == 1)
	{
		print_pointer(str_pointer, d, value);
		while (++i < value->width - actual_size(str_pointer, d, value))
			write(1, " ", 1);
	}
	else
	{
		while (++i < value->width - actual_size(str_pointer, d, value))
			write(1, " ", 1);
		print_pointer(str_pointer, d, value);
	}
	return (value->width);
}

int			pointer_proc(t_format *value, va_list *ap)
{
	unsigned long	d;
	char			*str_pointer;
	int				ret;

	d = va_arg(*ap, unsigned long);
	str_pointer = ft_itoa_base(d);
	ret = width_proc(value, str_pointer, d);
	free(str_pointer);
	return (ret);
}
