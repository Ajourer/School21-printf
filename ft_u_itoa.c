/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_u_itoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralverta <ralverta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 19:20:40 by ralverta          #+#    #+#             */
/*   Updated: 2021/01/27 19:59:57 by ralverta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	num_of_dig(unsigned int n)
{
	int		i;

	if (n == 0)
		return (1);
	i = 0;
	while (n != 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char		*ft_u_itoa(unsigned int n)
{
	char	*str;
	int		i;

	if (!(str = malloc(num_of_dig(n) + 1)))
		return (NULL);
	i = num_of_dig(n) - 1;
	str[i + 1] = '\0';
	if (n == 0)
		str[i] = '0';
	while (i >= 0 && n != 0)
	{
		str[i] = (n % 10) + '0';
		n /= 10;
		i--;
	}
	return (str);
}
