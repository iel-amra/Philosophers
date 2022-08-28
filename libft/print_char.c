/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 12:34:05 by iel-amra          #+#    #+#             */
/*   Updated: 2022/07/21 16:48:07 by iel-amra         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"
#include "ft_printf.h"

int	print_char(va_list args, char *flags, int fd)
{
	(void) flags;
	ft_putchar_fd(va_arg(args, int), fd);
	return (0);
}

int	len_print_char(va_list args, char *flags)
{
	(void) flags;
	(void) args;
	return (1);
}
