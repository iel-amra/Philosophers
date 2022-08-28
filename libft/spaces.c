/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 13:04:04 by iel-amra          #+#    #+#             */
/*   Updated: 2022/07/21 17:33:01 by iel-amra         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	get_width(char *flags)
{
	while (*flags && (*flags <= 48 || *flags > 57) && *flags != '.')
		flags++;
	return (ft_atoi(flags));
}

char	get_padding_type(char *flags)
{
	char	padding;

	padding = ' ';
	while (*flags && (*flags <= 48 || *flags > 57) && *flags != '.')
	{
		if (*flags == '0' && padding != '-' && !(ft_strchr(flags, '.')))
			padding = '0';
		if (*flags == '-')
			padding = '-';
		flags++;
	}
	return (padding);
}

int	spaces(int len, char *flags, int mode, int fd)
{
	int	width;
	int	padding;

	width = get_width(flags);
	padding = get_padding_type(flags);
	if (width > len && mode == 0 && (padding == ' ' || padding == '0'))
	{
		while (len < width)
		{
			write(fd, &padding, 1);
			len++;
		}
	}
	if (width > len && mode == 1 && padding == '-')
	{
		while (len < width)
		{
			write(fd, " ", 1);
			len++;
		}
	}
	return (len);
}
