/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralverta <ralverta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 00:31:33 by ralverta          #+#    #+#             */
/*   Updated: 2021/01/28 16:22:00 by ralverta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	processing(t_format *value, va_list *ap)
{
	int	length;

	length = 0;
	if (value->type == 'c' || value->type == '%')
		length = char_proc(value, ap);
	if (value->type == 's')
		length = string_proc(value, ap);
	if (value->type == 'd' || value->type == 'i')
		length = int_proc(value, ap);
	if (value->type == 'u')
		length = unsign_proc(value, ap);
	if (value->type == 'x' || value->type == 'X')
		length = hex_proc(value, ap);
	if (value->type == 'p')
		length = pointer_proc(value, ap);
	return (length);
}

int			ft_printf(const char *str, ...)
{
	va_list		ap;
	t_format	value;
	int			length;

	length = 0;
	value.i = 0;
	va_start(ap, str);
	while (str[value.i])
	{
		if (str[value.i] && str[value.i] != '%')
		{
			ft_putchar_fd(str[value.i], 1);
			value.i++;
			length++;
			continue;
		}
		value.i++;
		final_parse((char *)str, &ap, &value);
		length += processing(&value, &ap);
	}
	va_end(ap);
	return (length);
}
