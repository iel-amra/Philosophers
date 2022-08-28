/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 13:47:12 by iel-amra          #+#    #+#             */
/*   Updated: 2022/07/21 16:49:05 by iel-amra         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	len_integer(int n)
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

int	ft_putabs(long nb)
{
	if (nb < 0)
		nb *= -1;
	if (nb >= 10)
		ft_putabs(nb / 10);
	ft_putchar_fd(nb % 10 + 48, 1);
	return ((int) nb);
}

int	print_int(va_list args, char *flags, int fd)
{
	int	nb;
	int	len;
	int	prec;

	nb = va_arg(args, int);
	len = len_integer(nb);
	prec = preci(flags);
	while (prec > len)
	{
		write(fd, "0", 1);
		len++;
	}
	ft_putabs(nb);
	return (0);
}

int	len_print_int(va_list args, char *flags)
{
	va_list	dup_args;
	int		nb;
	int		len;
	int		prec;

	va_copy(dup_args, args);
	nb = va_arg(dup_args, int);
	len = len_integer(nb);
	prec = preci(flags);
	va_end(dup_args);
	while (prec > len)
		len++;
	return (len);
}
