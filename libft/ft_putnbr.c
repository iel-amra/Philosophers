/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:46:49 by iel-amra          #+#    #+#             */
/*   Updated: 2021/11/05 19:30:10 by iel-amra         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr(int n)
{
	char	c;
	int		neg;

	neg = 1;
	if (n < 0)
	{
		write(1, "-", 1);
		neg = -1;
	}
	if (n >= 10 || n <= -10)
		ft_putnbr(n / 10 * neg);
	c = n % 10 * neg + 48;
	write(1, &c, 1);
}