/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralverta <ralverta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 18:58:30 by ralverta          #+#    #+#             */
/*   Updated: 2021/01/28 16:29:25 by ralverta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	num_of_dig(unsigned long n)
{
	int		i;

	if (n == 0)
		return (1);
	i = 0;
	while (n != 0)
	{
		i++;
		n /= 16;
	}
	return (i);
}

static char	digit(unsigned long n)
{
	return (n < 10 ? n + '0' : n - 10 + 'a');
}

char		*ft_itoa_base(unsigned long n)
{
	char	*str;
	int		num;

	num = num_of_dig(n);
	if (!(str = malloc(num + 1)))
		return (NULL);
	str[num] = '\0';
	while (--num >= 0)
	{
		str[num] = digit(n % 16);
		n /= 16;
	}
	return (str);
}
