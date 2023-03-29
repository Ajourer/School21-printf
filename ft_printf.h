/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralverta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 10:14:01 by ralverta          #+#    #+#             */
/*   Updated: 2021/01/28 16:39:50 by ralverta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <limits.h>
# include "libft/libft.h"

typedef struct	s_format {
	char		type;
	int			width;
	int			precision;
	int			flag_zero;
	int			flag_minus;
	int			i;
}				t_format;

int				ft_printf(const char *str, ...);
void			final_parse(char *str, va_list *ap, t_format *value);
int				char_proc(t_format *value, va_list *ap);
int				string_proc(t_format *value, va_list *ap);
int				int_proc(t_format *value, va_list *ap);
int				unsign_proc(t_format *value, va_list *ap);
int				hex_proc(t_format *value, va_list *ap);
int				pointer_proc(t_format *value, va_list *ap);
int				abs_(int n);
char			*ft_u_itoa(unsigned int n);
char			*ft_itoa_base(unsigned long n);
char			*str_upper(char *str);

#endif
