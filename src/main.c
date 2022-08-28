/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:24:01 by iel-amra          #+#    #+#             */
/*   Updated: 2022/08/25 17:59:28 by iel-amra         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>

void	*test(void	*args)
{
	(void) args;
	ft_dprintf(2, "Hello from thread\n");
	return ((void *) 0);
}

int	main(int argc, char **argv)
{
	pthread_t	thread;

	(void) argc;
	(void) argv;

	pthread_create(&thread, (void *) 0, test, (void *) 0);
	return (0);
}
