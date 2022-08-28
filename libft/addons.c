/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addons.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 19:38:33 by iel-amra          #+#    #+#             */
/*   Updated: 2022/07/21 16:43:06 by iel-amra         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	addons_int(va_list args, char *flags, int len, int mode_fd)
{
	va_list	dup;
	char	padd;

	padd = get_padding_type(flags);
	va_copy(dup, args);
	if (va_arg(dup, int) < 0)
	{
		va_end(dup);
		if ((mode_fd < 0 && padd == '0') || (mode_fd >= 0 && padd != '0'))
			write(ft_abs(mode_fd), "-", 1);
		return (len + (mode_fd < 0));
	}
	va_end(dup);
	if ((ft_strchr(flags, '+') && padd == '0' && mode_fd < 0)
		|| (ft_strchr(flags, '+') && padd != '0' && mode_fd >= 1))
		write(ft_abs(mode_fd), "+", 1);
	if ((ft_strchr(flags, ' ') && !ft_strchr(flags, '+')
			&& padd == '0' && mode_fd < 0)
		|| (ft_strchr(flags, ' ') && !ft_strchr(flags, '+')
			&& padd != '0' && mode_fd >= 0))
		write(ft_abs(mode_fd), " ", 1);
	if ((ft_strchr(flags, '+') || ft_strchr(flags, ' ')) && mode_fd < 0)
		return (len + 1);
	return (len);
}

int	addons_little_hexa(va_list args, char *flags, int len, int mode_fd)
{
	va_list	dup;

	va_copy(dup, args);
	if (va_arg(dup, int) == 0)
	{
		va_end(dup);
		return (len);
	}
	va_end(dup);
	if (ft_strchr(flags, '#') && get_padding_type(flags) == '0' && mode_fd < 0)
		write(ft_abs(mode_fd), "0x", 2);
	if (ft_strchr(flags, '#') && get_padding_type(flags) != '0' && mode_fd >= 0)
		write(ft_abs(mode_fd), "0x", 2);
	if (ft_strchr(flags, '#') && mode_fd < 0)
		return (len + 2);
	return (len);
}

int	addons_big_hexa(va_list args, char *flags, int len, int mode_fd)
{
	va_list	dup;

	va_copy(dup, args);
	if (va_arg(dup, int) == 0)
	{
		va_end(dup);
		return (len);
	}
	va_end(dup);
	if (ft_strchr(flags, '#') && get_padding_type(flags) == '0' && mode_fd < 0)
		write(ft_abs(mode_fd), "0X", 2);
	if (ft_strchr(flags, '#') && get_padding_type(flags) != '0' && mode_fd >= 1)
		write(ft_abs(mode_fd), "0X", 2);
	if (ft_strchr(flags, '#') && mode_fd < 0)
		return (len + 2);
	return (len);
}
