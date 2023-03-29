/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_proc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralverta <ralverta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 18:45:49 by ralverta          #+#    #+#             */
/*   Updated: 2021/01/28 11:42:24 by ralverta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	putstr_precision(char *s, t_format *value)
{
	int j;

	j = -1;
	if (value->precision > 0 && value->precision < (int)ft_strlen(s))
	{
		while (++j < value->precision)
			write(1, &(s[j]), 1);
	}
	if (value->precision == -1 || value->precision >= (int)ft_strlen(s))
		ft_putstr_fd(s, 1);
}

static int	size_with_precision(char *s, t_format *value)
{
	if (value->precision != -1 && value->precision < (int)ft_strlen(s))
		return (value->precision);
	else
		return (ft_strlen(s));
}

int			string_proc(t_format *value, va_list *ap)
{
	char	*s;
	int		i;

	i = -1;
	s = va_arg(*ap, char *);
	if (!s)
		s = "(null)";
	if (value->width < size_with_precision(s, value))
	{
		putstr_precision(s, value);
		return (size_with_precision(s, value));
	}
	if (value->flag_minus == 1)
	{
		putstr_precision(s, value);
		while (++i < value->width - size_with_precision(s, value))
			write(1, " ", 1);
	}
	else
	{
		while (++i < value->width - size_with_precision(s, value))
			write(1, " ", 1);
		putstr_precision(s, value);
	}
	return (size_with_precision(s, value) + i);
}
