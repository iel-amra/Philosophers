/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 16:05:53 by iel-amra          #+#    #+#             */
/*   Updated: 2022/07/21 16:53:25 by iel-amra         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_big_hexa(va_list args, char *flags, int fd)
{
	long int	nb;
	int			len;
	int			prec;

	nb = (long int) va_arg(args, unsigned int);
	len = len_long_hexa(nb);
	prec = preci(flags);
	while (prec > len)
	{
		write(fd, "0", 1);
		len++;
	}
	ft_putulong_hexa((unsigned long) nb, 55, fd);
	return (0);
}

int	len_print_big_hexa(va_list args, char *flags)
{
	va_list		dup_args;
	long int	nb;
	int			len;
	int			prec;

	va_copy(dup_args, args);
	nb = va_arg(dup_args, unsigned int);
	va_end(dup_args);
	len = len_long_hexa(nb);
	prec = preci(flags);
	while (prec > len)
		len++;
	return (len);
}
