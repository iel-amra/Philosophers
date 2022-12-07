/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:24:01 by iel-amra          #+#    #+#             */
/*   Updated: 2022/12/01 18:14:47 by iel-amra         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int	main(int argc, char **argv)
{
	t_table	table;
	int		ret;

	ret = 0;
	if (init(&table, argc, argv))
		return (1);
	if (start_philosophers(&table))
		ret = 1;
	/*
	waiting_finish(*table);
	*/
	destroy_all_mutex(&table);
	free_memory(&table);
	return (ret);
}
