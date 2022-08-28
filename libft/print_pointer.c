/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:06:05 by iel-amra          #+#    #+#             */
/*   Updated: 2022/07/21 17:38:55 by iel-amra         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	one_hexa(unsigned char c, int decal, int fd)
{
	if (c <= 9)
		ft_putchar_fd(c + 48, fd);
	else
		ft_putchar_fd(c + decal, fd);
}

void	ft_putulong_hexa(unsigned long n, int decal, int fd)
{
	if (n >= 16)
		ft_putulong_hexa(n / 16, decal, fd);
	one_hexa(n % 16, decal, fd);
}

int	print_pointer(va_list args, char *flags, int fd)
{
	void	*pointeur;

	(void) flags;
	pointeur = va_arg(args, void *);
	ft_putstr_fd("0x", fd);
	ft_putulong_hexa((unsigned long) pointeur, 87, fd);
	return (0);
}

int	len_print_pointer(va_list args, char *flags)
{
	va_list	dup_args;
	void	*pointeur;

	(void) flags;
	va_copy(dup_args, args);
	pointeur = va_arg(dup_args, void *);
	va_end(dup_args);
	return (len_long_hexa((unsigned long) pointeur) + 2);
}
