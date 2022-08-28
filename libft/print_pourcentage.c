/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pourcentage.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 16:14:00 by iel-amra          #+#    #+#             */
/*   Updated: 2022/07/21 17:39:17 by iel-amra         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_pourcentage(va_list args, char *flags, int fd)
{
	(void) args;
	(void) flags;
	write(fd, "%", 1);
	return (0);
}

int	len_print_pourcentage(va_list args, char *flags)
{
	(void) args;
	(void) flags;
	return (1);
}
