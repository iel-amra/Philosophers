/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   psf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:32:32 by iel-amra          #+#    #+#             */
/*   Updated: 2022/07/21 17:50:33 by iel-amra         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_functions(int (*f[9])(va_list, char *, int))
{
	f[0] = &print_char;
	f[1] = &print_string;
	f[2] = &print_pointer;
	f[3] = &print_int;
	f[4] = &print_int;
	f[5] = &print_unsigned_int;
	f[6] = &print_little_hexa;
	f[7] = &print_big_hexa;
	f[8] = &print_pourcentage;
}

void	get_len_functions(int (*f[9])(va_list, char *))
{
	f[0] = &len_print_char;
	f[1] = &len_print_string;
	f[2] = &len_print_pointer;
	f[3] = &len_print_int;
	f[4] = &len_print_int;
	f[5] = &len_print_unsigned_int;
	f[6] = &len_print_little_hexa;
	f[7] = &len_print_big_hexa;
	f[8] = &len_print_pourcentage;
}

int	rang(char c)
{
	char	*charset;

	charset = CHARSET;
	return (ft_strchr(charset, c) - charset);
}

int	add_rang(char c)
{
	char	*liste;

	liste = "idxX";
	return (ft_strchr(liste, c) - liste);
}

void	get_addons(int (*f[4])(va_list, char *, int, int))
{
	f[0] = &addons_int;
	f[1] = &addons_int;
	f[2] = &addons_little_hexa;
	f[3] = &addons_big_hexa;
}
