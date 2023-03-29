/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralverta <ralverta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 15:08:03 by ralverta          #+#    #+#             */
/*   Updated: 2021/01/27 17:00:08 by ralverta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	char_proc(t_format *value, va_list *ap)
{
	char	c;
	int		i;

	if (value->type == '%')
		c = '%';
	else
		c = (char)va_arg(*ap, int);
	i = 0;
	if (value->flag_minus == 1)
	{
		write(1, &c, 1);
		while (++i < value->width)
			write(1, " ", 1);
		return (i);
	}
	else
	{
		while (++i < value->width)
			write(1, value->flag_zero ? "0" : " ", 1);
		write(1, &c, 1);
		return (i);
	}
}
