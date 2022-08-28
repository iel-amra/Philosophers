/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned_int.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 13:53:31 by iel-amra          #+#    #+#             */
/*   Updated: 2022/07/21 16:56:51 by iel-amra         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	len_uinteger(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

void	ft_putulong(unsigned long int n, int fd)
{
	char	c;

	if (n >= 10)
		ft_putulong(n / 10, fd);
	c = n % 10 + 48;
	write(fd, &c, 1);
}

int	print_unsigned_int(va_list args, char *flags, int fd)
{
	unsigned int	nb;
	int				prec;
	int				len;

	nb = va_arg(args, unsigned int);
	len = len_uinteger(nb);
	prec = preci(flags);
	while (prec > len)
	{
		write(fd, "0", 1);
		len++;
	}
	ft_putulong(nb, fd);
	return (0);
}

int	len_print_unsigned_int(va_list args, char *flags)
{
	va_list			dup_args;
	unsigned int	nb;
	int				len;
	int				prec;

	va_copy(dup_args, args);
	nb = va_arg(dup_args, unsigned int);
	len = len_uinteger(nb);
	prec = preci(flags);
	while (prec > len)
		len++;
	va_end(dup_args);
	return (len);
}
