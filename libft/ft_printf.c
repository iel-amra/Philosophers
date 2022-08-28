/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:20:26 by iel-amra          #+#    #+#             */
/*   Updated: 2022/08/15 10:46:25 by iel-amra         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	nb_flags(const char *str)
{
	int		i;
	char	*charset;

	i = 0;
	charset = CHARSET;
	while (str[i] && !ft_strchr(charset, str[i]))
		i++;
	return (i);
}

int	valid_flags(char *flags)
{
	char	*v_flags;

	v_flags = V_FLAGS;
	while (*flags != '\0' && ft_strchr(v_flags, *flags))
		flags++;
	while (ft_isdigit(*flags))
		flags++;
	if (*flags == '.')
		flags++;
	while (ft_isdigit(*flags))
		flags++;
	if (*flags)
		return (0);
	return (1);
}

int	print_var(char c, va_list args, char *flags, int fd)
{
	int		len;
	int		(*f[18])(va_list, char *, int);
	int		(*f_len[18])(va_list, char *);
	int		(*addons[4])(va_list, char *, int, int);

	get_functions(f);
	get_len_functions(f_len);
	get_addons(addons);
	len = (*f_len[rang(c)])(args, flags);
	if (c == 'i' || c == 'd' || c == 'x' || c == 'X')
		len = (*addons[add_rang(c)])(args, flags, len, fd);
	len = spaces(len, flags, 0, fd);
	if (c == 'i' || c == 'd' || c == 'x' || c == 'X')
		len = (*addons[add_rang(c)])(args, flags, len, -fd);
	(*f[rang(c)])(args, flags, fd);
	len = spaces(len, flags, 1, fd);
	return (len);
}

int	print_var_if_charset(const char **str, va_list args, int fd)
{
	char	*charset;
	char	*flags;
	int		count;
	int		i;

	i = 0;
	count = 0;
	charset = CHARSET;
	flags = ft_calloc(nb_flags(*str) + 1, sizeof(char));
	if (!flags)
		return (-1);
	while ((*str)[i] && !ft_strchr(charset, (*str)[i]))
	{
		flags[i] = (*str)[i];
		i++;
	}
	flags[i] = '\0';
	if (valid_flags(flags) && (*str)[i])
	{
		*str = *str + i;
		count = print_var(**str, args, flags, fd);
		(*str)++;
	}
	free(flags);
	return (count);
}

int	ft_vprintf(int fd, const char *str, va_list args)
{
	int		count;
	int		check;

	count = 0;
	while (*str)
	{
		if (*str != '%')
		{
			ft_putchar_fd(*str, fd);
			str++;
			count++;
		}
		else
		{
			str++;
			check = print_var_if_charset(&str, args, fd);
			if (check == -1)
				return (-1);
			count += check;
		}
	}
	return (count);
}
