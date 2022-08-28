/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 16:05:53 by iel-amra          #+#    #+#             */
/*   Updated: 2022/07/21 17:38:42 by iel-amra         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
/*
int	len_long_hexa(unsigned long int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len++;
	while (n != 0)
	{
		n /= 16;
		len++;
	}
	return (len);
}*/

int	print_hexa(va_list args, char *flags, int decal, int fd)
{
	long int	nb;
	int			len;

	(void) flags;
	nb = (long int) va_arg(args, int);
	len = len_long_hexa(nb);
	if (nb < 0)
	{
		nb *= -1;
		write(fd, "-", 1);
	}
	ft_putulong_hexa((unsigned long) nb, decal, fd);
	return (len);
}
