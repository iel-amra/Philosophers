/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overflow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:37:57 by iel-amra          #+#    #+#             */
/*   Updated: 2022/12/01 14:05:01 by iel-amra         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int	nb_digit(unsigned int nb)
{
	int	i;

	i = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

int	overflow(char *str, unsigned int nb, int len)
{
	int				res;

	if (nb / 10)
	{
		res = overflow(str, nb / 10, len - 1);
		if (res != 0)
			return (res);
	}
	if (str[len] < (char)(nb % 10 + '0'))
		return (-1);
	if (str[len] > (char)(nb % 10 + '0'))
		return (1);
	return (0);
}

int	fit_in_int(char *str)
{
	if (ft_strlen(str) > nb_digit(INT_MAX) && *str != '-')
		return (0);
	if (ft_strlen(str) - 1 > nb_digit(-INT_MIN) && *str == '-')
		return (0);
	if (ft_strlen(str) < nb_digit(INT_MAX) && *str != '-')
		return (1);
	if (ft_strlen(str) - 1 < nb_digit(INT_MIN) && *str == '-')
		return (1);
	if (*str != '-' && overflow(str, INT_MAX, nb_digit(INT_MAX) - 1) == 1)
		return (0);
	if (*str == '-' && overflow(str + 1, -INT_MIN, nb_digit(INT_MIN) - 1) == 1)
		return (0);
	return (1);
}
