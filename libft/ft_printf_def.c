/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_def.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 10:26:57 by iel-amra          #+#    #+#             */
/*   Updated: 2022/08/15 10:46:17 by iel-amra         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_dprintf(int fd, const char *str, ...)
{
	va_list	args;

	va_start(args, str);
	va_end(args);
	return (ft_vprintf(fd, str, args));
}

int	ft_printf(const char *str, ...)
{
	va_list	args;

	va_start(args, str);
	va_end(args);
	return (ft_vprintf(1, str, args));
}
